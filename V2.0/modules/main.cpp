#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <chrono>
#include "reading.h"
#include "euclidean_distance.h"
#include "FilteredVamana.h"
#include "FilteredGreedySearch.h"
#include "Stitched.h"
#include "groundtruth.h"
#include "reading_groundtruth.h"
#include "json.hpp"
#include <omp.h>

//define the json from the nlohmann library
using json = nlohmann::json;

using namespace std;
using namespace chrono;



json readConfig(const string& config_filename) {
    json config_data;

    ifstream config_file(config_filename);
    
    if(!config_file.is_open())
        throw runtime_error("Unable to open config file.");

    config_file >> config_data;

    config_file.close();

    return config_data;
}


int main(int argc, char **argv) {

    json config = readConfig("../../.vscode/config2.json");

    //extract variables from configuration
    string source_path = config["source_path"];
    string query_path = config["query_path"];
    int num_data_dimensions = config["num_data_dimensions"];
    int num_query_dimensions = num_data_dimensions + static_cast<int>(config["num_query_dimensions_offset"]);
    float sample_proportion = config["sample_proportion"];
    double alpha = config["alpha"];
    int R = config["R"];
    int knn = config["knn"];
    int L_sizelist = config["L_sizelist"];
    int R_small = config["Rsmall"];
    int L_small = config["Lsmall"];
    int R_stitched = config["Rstitched"];
    cout<<"The parameters are:\n a="<<alpha<<" R="<<R<<" knn="<<knn<<" L_siselist="<<L_sizelist<<" R_small="<<R_small<<" L_small="<<L_small<<" R_stitched="<<R_stitched<<endl;
    auto start = system_clock::now();
    // Read data points
    vector <vector<float>> DataNodes;
    set <float> category_attributes;
    category_attributes= ReadBin(source_path, num_data_dimensions, DataNodes); //DataNode is the database, attributes is the set which have all the categories each vector can have)
    for (set <float> ::iterator categories=category_attributes.begin();categories!=category_attributes.end();categories++){
        cout <<*categories << " ";
    }
   
    vector <vector<float>> queries;
    ReadBin(query_path, num_query_dimensions, queries);

    

    int vector_number = int (DataNodes.size());
    int query_number = int (queries.size());

    vector<int>queries_to_delete;

    //removing the queries with type>1
for(int i=0;i<query_number;i++){
    if(queries[i][0]>1)
        queries_to_delete.push_back(i);
}
for (int i = queries_to_delete.size() - 1; i >= 0; --i) {
    queries.erase(queries.begin() + queries_to_delete[i]);
}
    query_number = queries.size(); //updating the size of queries with the remaining elemtod of type 0 && 1
    vector<vector<int>> ground; //the groundtuth for each query node will be saved here

    //calculating the euclidean distaances
    vector<vector<double>> vecmatrix(vector_number,vector<double>(vector_number));  //10000 *10000 matrix for the euclidean distance of every node between every node
    vector <vector <double>> querymatrix(vector_number,vector<double>(query_number)); // 10000 *100 matrix which calculates the euclidean distance between database node and queries

    auto time_before =system_clock::now();
    euclidean_distance_of_database(DataNodes,vecmatrix); //calculating the euclidean distances of the whole database of nodes with each other
    euclidean_distance_of_queries (DataNodes,queries,querymatrix); //calculating the euclidean distances between the nodes of database and each querie vector
    auto time_now = system_clock::now();
    duration <double> elapsed = time_now - time_before;
    cout<<"The euclidean caclulations take: "<< elapsed.count()<<endl;

    //writing groundtruth into a txt file and giving values into ground vector in order to exctract recall later.
    time_before = system_clock::now();
    groundtruth(DataNodes,queries,vecmatrix,querymatrix,ground); //uncomment only if you want calculate from scrath the groundtruth of a dataset
    time_now = system_clock::now();
    elapsed = time_now - time_before;
    cout<< " The groundtuth took "<<elapsed.count()<<endl;
    //ground = reading_groundtruth();

    
    //calculatin medoid
    time_before = system_clock :: now();
    map<float,int> M =FindMedoid(DataNodes,1,category_attributes); //r=1;
    time_now = system_clock::now();
    elapsed = time_now - time_before;
    cout<<"the time for caclulating medoid is "<<elapsed.count()<<endl;

    //calling StitchedVamana
    map <int,set<int>> Vamana_graph = StitchedVamana( DataNodes, category_attributes,
    alpha, L_small, R_small, R_stitched,vecmatrix,
    M);
    
    //initializing variables which are gonna be used in recall calculation
    vector<int>starting_nodes_for_unfiltered_search; 
    pair <set<pair<double,int>>,set<int>> PairVector;
    vector<float> accuracyS;
    vector<float>accuracyF;
    float total_recall=0;
    int stitched_filtered_count=0;
    float stitched_unfiltered_accuracy=0;
    float stitched_filtered_accuracy = 0;
    float accuracy;
    //for every query, we find its recall then we add this value into a counter and we divide with the total_recall/queries.size()
    //resulting into the total_recall. We also calculate the sub-recalls specifically for filtered or unfiltered queries.
    for(int j=0;j<query_number;j++){
        vector <float> Fq= {queries[j ][1]};
        
        PairVector = FilteredGreedy(Vamana_graph,j ,knn,L_sizelist,M,Fq,querymatrix,DataNodes,category_attributes);
            int counter=0;
            for(set<pair<double,int>>::iterator Lit=PairVector.first.begin();Lit!=PairVector.first.end();Lit++){
                    if(find(ground[j].begin(),ground[j].end(),Lit->second)!=ground[j].end())
                        counter++;
            }
        accuracy = float(counter) /100; //casting float because it was turning into an integer without it
        accuracyS.push_back(accuracy);
        if(Fq[0]!=-1){
            stitched_filtered_count++;
            stitched_filtered_accuracy+=accuracy;
        }
        else{
            stitched_unfiltered_accuracy+=accuracy;
        }
        total_recall+=accuracy;
    }
    float stitched_recall=total_recall/queries.size();
        

        //that was in oredr to print the recall for each node
        // for(int i=0;i<query_number;i++){
        //     cout<<"for query"<<i<<" ";
        //     for(auto accuracy : accuracyS[i]){
        //         cout<<accuracy<<", ";
        //         if(queries[i][1]==-1)
        //             stitched_unfiltered_accuracy+=accuracy;
        //         else{
        //             stitched_filtered_accuracy+=accuracy;
        //         }
        //         total_recall+=accuracy;
        //     }

        // }

    //same logic applies here.
        
    Vamana_graph = FilteredVamanaIndex(vecmatrix,DataNodes,alpha,R,category_attributes,M);
    int filtered_counter=0;
    int unfiltered_counter=0;
    float filtered_accuracy=0.0;
    float unfiltered_accuracy =0.0;
    L_sizelist = 300;
    map<float,int> new_M;
    total_recall = 0;
    for(int j=0; j<query_number;j++){
        vector<float> Fq = {queries[j][1]};
        if(Fq[0]== - 1){
            for(auto filters :category_attributes){
                vector<float>Fq_for_unfiltered = {filters};
                PairVector = FilteredGreedy(Vamana_graph,j,1,L_sizelist,M,Fq_for_unfiltered,querymatrix,DataNodes,category_attributes);
                set<pair<double,int>> node = PairVector.first;
                
                auto node_to_insert = node.begin(); //iterating the pair in order to add the int node in starting_nodes
                new_M[filters]= node_to_insert->second;
            }

            PairVector = FilteredGreedy(Vamana_graph,j,knn,L_sizelist,new_M,Fq,querymatrix,DataNodes,category_attributes);
            unfiltered_counter++;

    }
    else{
        PairVector = FilteredGreedy(Vamana_graph,j,knn,L_sizelist,M,Fq,querymatrix,DataNodes,category_attributes);
        filtered_counter++;
    }

    int counter=0;
    for(set<pair<double,int>>::iterator Lit=PairVector.first.begin();Lit!=PairVector.first.end();Lit++){
        if(find(ground[j].begin(),ground[j].end(),Lit->second)!=ground[j].end())
            counter++;
    }
    float accuracy = float(counter) /100; //casting float because it was turning into an integer without it
    accuracyF.push_back(accuracy);
    total_recall+=accuracy;
    if(Fq[0] != -1)
        filtered_accuracy+=accuracy;
    else
        unfiltered_accuracy+=accuracy;

    }

    //that was in oredr to print the recall for each node
    //printing the recall of each node
    //  cout<<"the accuarcy for each query is:"<<endl;
    //     for(int i=0;i<query_number;i++){
    //         cout<<"for query"<<i<<" ";
    //         for(auto accuracy : accuracyF[i]){
    //             cout<<accuracy<<", ";
    //         }

    //     }
    
    cout<<endl<<"THE TOTAL RECALL FOR Filtered IS: "<<total_recall/queries.size()<<endl;
    cout<< "The recall for filtered queries is:"<<filtered_accuracy/filtered_counter;
    cout<<"The recall for unfiltered queries in filteredVamana is"<<unfiltered_accuracy/unfiltered_counter<<endl;

    
    // int i=0;
    // int belowninetyS=0;
    // int belowninetyF=0;
    // for(auto ratio : accuracyS ){
    //     if(ratio<0.9)
    //         belowninetyS++;
    //     cout<<"query "<<i<< "has" <<ratio<<"ratio"<<endl;
    //     i++;
    // }
    // for (auto ratio : accuracyF){
    //     if(ratio<0.9){
    //         belowninetyF++;
    //     }
    // }


    cout<<endl<<"THE TOTAL RECALL FOR STITCHED IS"<<stitched_recall<<endl;
    unfiltered_counter= int(queries.size())-stitched_filtered_count;
    cout<<"the recall for stitched unfiltered nodes is"<<float(stitched_unfiltered_accuracy/unfiltered_counter)<<endl;;
  
    cout<<"the recall for stitched filtered node is" <<stitched_filtered_accuracy/stitched_filtered_count<<endl;
    // cout<< "The total nuber of queries under 90 for stitched accuracy is "<<belowninetyS;
    // cout<< "The total nuber of queries under 90 for FILTERED accuracy is "<<belowninetyF;

    
    auto end = std:: chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout<<"the elapsed time is "<<elapsed_seconds.count()<<endl;

    cout <<endl;
    
}






















//     std::cout << "The queries are:" << std::endl;
// for (size_t i = 0; i < queries.size(); i++) { // Use size_t for indices
//     std::cout << "Query " << i << ": ";      // Better formatting
//     for (const auto &node : queries[i]) {    // Use const auto& to avoid unnecessary copies
//         std::cout << node << " ";
//     }
//     std::cout << std::endl;
// }

    
    // cout << "the dataset is:" << endl;
    // for(int i=0;i<int(DataNodes.size());i++){
    //     cout<< endl<<"for node "<<i<<"the distances are: ";
    //     for(vector<float> ::iterator datanodes=DataNodes[i].begin();datanodes!=DataNodes[i].end();datanodes++){
    //         cout << *datanodes <<" ";
    // }

    // }

    //set<pair<double,int>> K_neighbors= PairVector.first;
    // cout<<"K_neighbors are: "<<K_neighbors.size()<<endl;
    // cout<<"neighbors for query[1] are:";
    // for(auto neighbors : K_neighbors){
    //     cout<< neighbors.second <<", "; //printing the int node
    // }


























