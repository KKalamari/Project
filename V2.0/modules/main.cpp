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
#include "StitchedVamana.h"
#include "json.hpp"

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
    int Rsmall = config["Rsmall"];
    int Lsmall = config["Lsmall"];
    int Rstitched = config["Rstitched"];

    //read data points
    vector <vector<float>> DataNodes;
    set <float> category_attributes;
    category_attributes= ReadBin(source_path, num_data_dimensions, DataNodes); //DataNode is the database, attributes is the set which have all the categories each vector can have)
    cout <<"the size of category attributes is "<<category_attributes.size()<<endl;
    for (set <float> ::iterator categories=category_attributes.begin();categories!=category_attributes.end();categories++){
        cout <<*categories << " ";
    }
    cout<<"the size of category attributes are:"<<category_attributes.size();
    cout <<endl;
   // Read queries
    int num_query_dimensions = num_data_dimensions + 2;
    vector <vector<float>> queries;
    ReadBin(query_path, num_query_dimensions, queries);
    
    map<float,set<int>> labels;

     for (auto category : category_attributes) {
        for(int node=0;node< DataNodes.size();node++){
            if(DataNodes[node][0]== category)
                labels[category].insert(node);

        }
      
    }

    int vector_number = int (DataNodes.size());
    int query_number = int (queries.size());

    vector<vector<double>> vecmatrix(vector_number,vector<double>(vector_number));  //10000 *10000 matrix for the euclidean distance of every node between every node
    vector <vector <double>> querymatrix(vector_number,vector<double>(query_number)); // 10000 *100 matrix which calculates the euclidean distance between database node and queries
    euclidean_distance_of_database(DataNodes,vecmatrix); //calculating the euclidean distances of the whole database of nodes with each other
    euclidean_distance_of_queries (DataNodes,queries,querymatrix); //calculating the euclidean distances between the nodes of database and each querie vector
    cout<<" I am after calculating euclidean distances"<<endl;



    map<float,int> M =FindMedoid(DataNodes,1,category_attributes); //r=1;
    map<int,set<int>> Vamana_graph = FilteredVamanaIndex(vecmatrix,DataNodes,alpha,R,category_attributes,M);
    cout <<"vamana graph size is: "<< Vamana_graph.size()<<endl;
    vector <float> Fq= {queries[1][1]};
    cout<<"the Fq is "<<queries[1][1]<<endl;
    pair <set<pair<double,int>>,set<int>> PairVector;
    PairVector = FilteredGreedy(Vamana_graph,1,knn,L_sizelist,M,Fq,querymatrix,DataNodes);
    set<pair<double,int>> K_neighbors= PairVector.first;
    cout<<"K_neighbors are: "<<K_neighbors.size()<<endl;
    cout<<"neighbors for query[1] are:";
    for(auto neighbors : K_neighbors){
        cout<< neighbors.second <<", "; //printing the int node
    }
    //   cout << "Running StitchedVamana..." << endl;

    // auto start = chrono::high_resolution_clock::now(); // Start timing

    // auto stitchedGraph = StitchedVamana(DataNodes, labels, alpha, Rsmall, Lsmall, Rstitched, vecmatrix);

    // auto end = chrono::high_resolution_clock::now(); // End timing
    // chrono::duration<double> elapsed = end - start;

    // cout << "StitchedVamana completed in " << elapsed.count() << " seconds" << endl;

    // // Print results
    // cout << "Stitched graph size: " << stitchedGraph.size() << endl;
    // for (const auto& [node, neighbors] : stitchedGraph) {
    //     cout << "Node " << node << " -> Neighbors: ";
    //     for (const auto& neighbor : neighbors) {
    //         cout << neighbor << " ";
    //     }
    //     cout << endl;
    // }

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