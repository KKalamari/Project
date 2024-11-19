#include <fstream>
#include <iostream>
#include <vector>
#include "reading.h"
#include <set>
#include <map>
#include "euclidean_distance.h"
#include "FilteredVamana.h"
#include "FilteredGreedySearch.h"

using namespace std;
int main(int argc, char **argv) {
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
    cout <<"the categories are:";
    cout <<"the size of category attributes is "<<category_attributes.size()<<endl;
    for (set <float> ::iterator categories=category_attributes.begin();categories!=category_attributes.end();categories++){
        cout <<*categories << " ";
    }
    cout <<endl;
   // Read queries
    int num_query_dimensions = num_data_dimensions + 2;
    vector <vector<float>> queries;
    ReadBin(query_path, num_query_dimensions, queries);
    // cout << "the dataset is:" << endl;
    // for(int i=0;i<int(DataNodes.size());i++){
    //     cout<< endl<<"for node "<<i<<"the distances are: ";
    //     for(vector<float> ::iterator datanodes=DataNodes[i].begin();datanodes!=DataNodes[i].end();datanodes++){
    //         cout << *datanodes <<" ";
    // }

    // }

    int vector_number = int (DataNodes.size());
    int query_number = int (queries.size());

    vector<vector<double>> vecmatrix(vector_number,vector<double>(vector_number));  //10000 *10000 matrix for the euclidean distance of every node between every node
    vector <vector <double>> querymatrix(vector_number,vector<double>(query_number)); // 10000 *100 matrix which calculates the euclidean distance between database node and queries
    euclidean_distance_of_database(DataNodes,vecmatrix); //calculating the euclidean distances of the whole database of nodes with each other
    euclidean_distance_of_queries (DataNodes,queries,querymatrix); //calculating the euclidean distances between the nodes of database and each querie vector
    cout<<" I am after calculating euclidean distances"<<endl;


    double alpha=1;
    int R=14;
    int knn=100;
    int L_sizelist=120;
    map<float,int> M =FindMedoid(DataNodes,1,category_attributes); //r=1;
    map<int,list<int>> Vamana_graph = FilteredVamanaIndex(vecmatrix,DataNodes,alpha,R,category_attributes,M);
    cout <<"I am after Vamana?!?!?!"<<endl;
    cout <<"vamana graph size is: "<< Vamana_graph.size()<<endl;
    int counter=0;
    for(int i =0;i<Vamana_graph.size();i++){
        cout <<"the neighbors of node "<< i <<"are: ";
        for(list<int>:: iterator mit=Vamana_graph[i].begin();mit!=Vamana_graph[i].end();mit++){
            cout<<*mit<<" ";
        }
    }
    vector <float> Fq= {queries[0][1]};
    pair <vector<int>,vector<int>> PairVector;
    PairVector = FilteredGreedy(Vamana_graph,0,knn,L_sizelist,M,Fq,querymatrix,DataNodes);
    vector<int> K_neighbors= PairVector.first;
    cout<<"neighbors for query[0] are:";
    for(auto neighbors : K_neighbors){
        cout<< neighbors <<" ";
    }
    cout <<endl;
    
}