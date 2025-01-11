#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <chrono>
#include "Reading.h"
#include "Euclidean_distance.h"
#include "FilteredVamana.h"
#include "FilteredGreedySearch.h"
#include "Stitched.h"
#include "groundtruth.h"
#include "reading_groundtruth.h"
#include "json.hpp"
#include <omp.h>


//L_sizelist increases the recall for the FilteredVamana algortihm, above 150 doesn't affect Stitched
//L_small increases the recall for the Stitched, above 200 doesn't affect FilteredVamana


//define the json from the nlohmann library
using json = nlohmann::json;

using namespace std;
using namespace chrono;

/*
reading the dataset and the queries for the specific dataset. Also it returns each different filter the dataset contains.
*/
set <float> reading_dataset_and_queries(string source_path,string query_path,int num_data_dimensions,int num_query_dimensions,vector<vector<float>>&Datanodes,vector <vector<float>>&queries){
    set <float> category_attributes;
    category_attributes= ReadBin(source_path, num_data_dimensions,Datanodes); //DataNode is the database, attributes is the set which have all the categories each vector can have)
    ReadBin(query_path, num_query_dimensions, queries);
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

    return category_attributes;

}

void Euclidean_caclulations(vector<vector<float>>& DataNodes,vector<vector<float>>&queries,vector<vector<double>>&vecmatrix,vector<vector<double>>&querymatrix,int thread_num){
    euclidean_distance_of_database(DataNodes,vecmatrix,thread_num); //calculating the euclidean distances of the whole database of nodes with each other
    euclidean_distance_of_queries (DataNodes,queries,querymatrix,thread_num); //calculating the euclidean distances between the nodes of database and each querie vector
}


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
    int thread_num=1; //it will be serial from default
    cout<<"The parameters are:\n a="<<alpha<<" R="<<R<<" knn="<<knn<<" L_siselist="<<L_sizelist<<" R_small="<<R_small<<" L_small="<<L_small<<" R_stitched="<<R_stitched<<endl;
    int m=1;
    int loops=1;
    int Do_I_calculate_groundtruth = 0; //by default it will read the groundtruth from the txt file instead of calculating it from scratch
    string function_to_run = "clean_run";
    if(argc > 1){
        loops =  atol(argv[1]);
        thread_num = atol(argv[2]);
        Do_I_calculate_groundtruth = atol(argv[3]);
        if(argc>4)
            function_to_run = argv[4];
    }
    cout <<"the instane will be executed for: "<<loops<<" times"<<endl;
    cout << "the thread_nums are"<<thread_num<<endl;
    cout<<"DO I Calc"<<Do_I_calculate_groundtruth<<endl;

    while(m<=loops){
        m++;
        auto starting_time_of_function = system_clock:: now();
        auto ending_time_of_funtion = system_clock::now();
        duration<double> elapsed_function_time;
        auto start = system_clock::now();
        // Read data points

        vector <vector<float>> DataNodes;
        set <float> category_attributes;
        vector <vector<float>> queries;
        if(function_to_run == "clean_run" || function_to_run =="Reading"|| function_to_run == "StitchedVamana" || function_to_run == "FilteredVamana"){
            starting_time_of_function = system_clock::now();
            category_attributes = reading_dataset_and_queries(source_path,query_path,num_data_dimensions,num_query_dimensions,DataNodes,queries);
            ending_time_of_funtion = system_clock::now();
            elapsed_function_time = ending_time_of_funtion - starting_time_of_function;
            cout<<"\nreading function took: "<<elapsed_function_time.count()<<endl;
        }
        if(!category_attributes.empty()){
        cout<<"\nthe filter categories are:";
            for (set <float> ::iterator categories=category_attributes.begin();categories!=category_attributes.end();categories++){
            cout <<*categories << " ";
        }
        cout<<endl;
        }
        
        FILE* output_file;
        output_file=fopen("execution_times.csv","a");

        int vector_number = int (DataNodes.size());
        int query_number = int (queries.size());

        //Initializing the matrixes where the euclidean distances from every node will be saved.
        vector<vector<double>> vecmatrix(vector_number,vector<double>(vector_number));  //10000 *10000 matrix for the euclidean distance of every node between every database node
        vector <vector <double>> querymatrix(vector_number,vector<double>(query_number)); // 10000 *100 matrix which calculates the euclidean distance between database node and queries node

        if(function_to_run == "clean_run" || function_to_run == "Euclidean" || function_to_run == "StitchedVamana" || function_to_run == "FilteredVamana"){     
            starting_time_of_function =system_clock::now();
            Euclidean_caclulations(DataNodes,queries,vecmatrix,querymatrix,thread_num);
            ending_time_of_funtion = system_clock::now();
            elapsed_function_time = ending_time_of_funtion - starting_time_of_function;
            cout<<"\nThe euclidean caclulations take: "<< elapsed_function_time.count()<<endl;
        }
        

        //writing groundtruth into a txt file and giving values into ground vector in order to exctract recall later.

        vector<vector<int>> ground; //the groundtuth for each query node will be saved here
        if(function_to_run == "clean_run" || function_to_run == "Groundtruth" || function_to_run == "StitchedVamana" || function_to_run == "FilteredVamana"){
            starting_time_of_function = system_clock ::now();
            if(Do_I_calculate_groundtruth==0){ //if it's zero we read the groundtruth that has already been calculated and saved in the txt file
                ground = reading_groundtruth();
                ending_time_of_funtion = system_clock::now();
                elapsed_function_time = ending_time_of_funtion-starting_time_of_function;
                cout<< "The groundtuth took "<<elapsed_function_time.count()<<endl;

            }
            else{ //else we calculate groundtruth from dcrath
                groundtruth(DataNodes,queries,vecmatrix,querymatrix,ground,thread_num); //uncomment only if you want calculate from scrath the groundtruth of a dataset
                ending_time_of_funtion = system_clock::now();
                elapsed_function_time = ending_time_of_funtion-starting_time_of_function;
                cout<< "The groundtuth took "<<elapsed_function_time.count()<<endl;
                }
        }

        //calculatin medoid
        map<float,int> M;
        if(function_to_run == "clean_run" || function_to_run == "Medoid" || function_to_run == "StitchedVamana" || function_to_run == "FilteredVamana"){
            starting_time_of_function = system_clock :: now();
            M =FindMedoid(DataNodes,1,category_attributes); //r=1;
            ending_time_of_funtion = system_clock::now();
            elapsed_function_time = ending_time_of_funtion - starting_time_of_function;
            cout<<" the time for caclulating medoid is "<<elapsed_function_time.count()<<endl;
        }

        //calling StitchedVamana
        pair <set<pair<double,int>>,set<int>> PairVector;
        map <int,set<int>> Vamana_graph;
        int unfiltered_counter=0;
        double stitched_recall=0;
        double Filtered_recall=0;

        if(function_to_run == "clean_run" || function_to_run == "StitchedVamana"){
            starting_time_of_function = system_clock::now();
            Vamana_graph = StitchedVamana( DataNodes, category_attributes,
            alpha, L_small, R_small, R_stitched,vecmatrix,
            M,thread_num);
            ending_time_of_funtion = system_clock::now();
            elapsed_function_time = ending_time_of_funtion - starting_time_of_function;
            cout<<"\nelapsed time of stitchedVamana is: "<<elapsed_function_time.count()<<endl;
            
            //initializing variables which are gonna be used in recall calculation
            vector<int>starting_nodes_for_unfiltered_search; 
            float total_recall=0;
            int stitched_filtered_count=0;
            float stitched_unfiltered_accuracy=0;
            float stitched_filtered_accuracy = 0;
            float accuracy;
            
            //for every query, we find its recall then we add this value into a counter and we divide with the total_recall/queries.size()
            //resulting into the total_recall. We also calculate the sub-recalls specifically for filtered or unfiltered queries.
            starting_time_of_function = system_clock::now();
            for(int j=0;j<query_number;j++){
                vector <float> Fq= {queries[j ][1]};
                PairVector = FilteredGreedy(Vamana_graph,j ,knn,L_small,M,Fq,querymatrix,DataNodes,category_attributes);
                    int counter=0;
                    for(set<pair<double,int>>::iterator Lit=PairVector.first.begin();Lit!=PairVector.first.end();Lit++){
                            if(find(ground[j].begin(),ground[j].end(),Lit->second)!=ground[j].end())
                                counter++;
                    }
                accuracy = float(counter) /knn; //casting float because it was turning into an integer without it
                if(Fq[0]!=-1){
                    stitched_filtered_count++;
                    stitched_filtered_accuracy+=accuracy;
                }
                else{
                    stitched_unfiltered_accuracy+=accuracy;
                }
                total_recall+=accuracy;
            }
            ending_time_of_funtion = system_clock::now();
            elapsed_function_time = ending_time_of_funtion - starting_time_of_function;
            cout << "elapsed time for recalling for stitched is "<< elapsed_function_time.count();
            stitched_recall=total_recall/queries.size();
            cout<<endl<<"THE TOTAL RECALL FOR STITCHED IS"<<stitched_recall<<endl;
            unfiltered_counter = query_number- stitched_filtered_accuracy;
            cout<<"the recall for stitched unfiltered nodes is"<<double(stitched_unfiltered_accuracy/unfiltered_counter)<<endl;;
        
            cout<<"the recall for stitched filtered node is" <<stitched_filtered_accuracy/stitched_filtered_count<<endl;
        }
            
        if(function_to_run == "clean_run" || function_to_run == "FilteredVamana"){
            starting_time_of_function = system_clock::now();
            Vamana_graph = FilteredVamanaIndex(vecmatrix,DataNodes,alpha,R,category_attributes,M,L_small);
            ending_time_of_funtion = system_clock::now();
            elapsed_function_time = ending_time_of_funtion - starting_time_of_function;
            cout << "\nelapsed time of FilteredVamana is "<<elapsed_function_time.count()<< endl;
            float filtered_accuracy=0.0;
            float unfiltered_accuracy =0.0;
            map<float,int> new_M;
            float total_recall = 0;
            starting_time_of_function = system_clock::now();
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

            }
            else{
                PairVector = FilteredGreedy(Vamana_graph,j,knn,L_sizelist,M,Fq,querymatrix,DataNodes,category_attributes);
            }

            int counter=0;
            for(set<pair<double,int>>::iterator Lit=PairVector.first.begin();Lit!=PairVector.first.end();Lit++){
                if(find(ground[j].begin(),ground[j].end(),Lit->second)!=ground[j].end())
                    counter++;
            }
            float accuracy = float(counter) /knn; //casting float because it was turning into an integer without it
            total_recall+=accuracy;
            if(Fq[0] != -1)
                filtered_accuracy+=accuracy;
            else
                unfiltered_accuracy+=accuracy;

            }
            ending_time_of_funtion = system_clock::now();
            elapsed_function_time = ending_time_of_funtion - starting_time_of_function;
            cout<< "the elapsed time of recalling for FilteredVamana is "<< elapsed_function_time.count()<<endl;

            
            Filtered_recall = total_recall/ query_number;
            cout<<endl<<"THE TOTAL RECALL FOR FILTERED IS: "<<Filtered_recall<<endl;
            cout<< "The recall for filtered queries is:"<<filtered_accuracy/ unfiltered_counter;
            cout<<"The recall for unfiltered queries in filteredVamana is"<<unfiltered_accuracy/unfiltered_counter<<endl;

        }

        auto end = system_clock::now();
        duration<double> elapsed_seconds = end - start;
        if(function_to_run=="clean_run")
            cout<<"the elapsed time is "<<elapsed_seconds.count()<<endl;

        fprintf(output_file,"\n%d, %d, %f, %d, %d, %d, %d, %d, %d, %f, %f, %f, %d\n",vector_number,query_number,alpha,R,knn,L_sizelist,R_small,L_small,R_stitched,Filtered_recall,stitched_recall,elapsed_seconds.count(),thread_num);

        cout <<endl;

        
    }

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


























