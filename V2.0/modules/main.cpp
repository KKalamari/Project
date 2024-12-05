#include <fstream>
#include <iostream>
#include <vector>
#include "reading.h"
#include <set>
#include <map>
#include "euclidean_distance.h"
#include "FilteredVamana.h"
#include "FilteredGreedySearch.h"
#include "groundtruth.h"
#include <chrono>
using namespace std;
int main(int argc, char **argv) {
    auto start = std:: chrono::system_clock::now();
    string source_path = "dummy-data.bin";
    string query_path = "dummy-queries.bin";

    // Also accept other path for source data
    if (argc > 1) {
    source_path = string(argv[1]);
    }

    int num_data_dimensions = 102;
    float sample_proportion = 0.001;

    // Read data points
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

    

    int vector_number = int (DataNodes.size());
    int query_number = int (queries.size());
    vector<int>queries_to_delete;
for(int i=0;i<query_number;i++){
    if(queries[i][0]>1)
        queries_to_delete.push_back(i);
}
for (int i = queries_to_delete.size() - 1; i >= 0; --i) {
    queries.erase(queries.begin() + queries_to_delete[i]);
}

    vector<vector<double>> vecmatrix(vector_number,vector<double>(vector_number));  //10000 *10000 matrix for the euclidean distance of every node between every node
    vector <vector <double>> querymatrix(vector_number,vector<double>(query_number)); // 10000 *100 matrix which calculates the euclidean distance between database node and queries
    euclidean_distance_of_database(DataNodes,vecmatrix); //calculating the euclidean distances of the whole database of nodes with each other
    euclidean_distance_of_queries (DataNodes,queries,querymatrix); //calculating the euclidean distances between the nodes of database and each querie vector
    cout<<" I am after calculating euclidean distances"<<endl;
   
    groundtruth(DataNodes,queries,vecmatrix,querymatrix); //uncomment only if you want calculate from scrath the groundtruth of a dataset
    
    double alpha=1;
    int R=14;
    int knn=100;
    int L_sizelist=120;
    map<float,int> M =FindMedoid(DataNodes,1,category_attributes); //r=1;
    map<int,set<int>> Vamana_graph = FilteredVamanaIndex(vecmatrix,DataNodes,alpha,R,category_attributes,M);
    cout <<"vamana graph size is: "<< Vamana_graph.size()<<endl;
    vector <float> Fq= {queries[5010 ][1]};
    cout<<"the Fq is "<<queries[5010 ][1]<<endl;
    cout<<"the query's type is: "<<queries[9850 ][0]<<endl;
    pair <set<pair<double,int>>,set<int>> PairVector;
    PairVector = FilteredGreedy(Vamana_graph,5010 ,knn,L_sizelist,M,Fq,querymatrix,DataNodes);
    set<pair<double,int>> K_neighbors= PairVector.first;
    cout<<"K_neighbors are: "<<K_neighbors.size()<<endl;
    cout<<"neighbors for query[5010] are:";
    for(auto neighbors : K_neighbors){
        cout<< neighbors.second <<", "; //printing the int node
    }
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