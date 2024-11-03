#include <iostream>
#include<vector>
#include "reading.h"
#include "graph_creation.h"
#include "greedysearch.h"
#include "euclidean_distance.h"
#include "vamana.h"
#include <list>
#include <utility>
#include <chrono>

using namespace std;
using namespace chrono;
// the syntax for execution  is: ./main k_num R_num


int main(int argc,char** argv){
    auto start = high_resolution_clock::now();
    const char* filename="siftsmall_base.fvecs";
    vector<vector<float>> vec; //structure where we gonna keep all the vectors from the dataset file
    vec=reading_fvecs(filename,1,10000);  
    int k_neigh; //the k nearest neighbors we want to find.
    int R; //The number which defines the random neighbors each node is going to have
    int a;
    if(argc>1){ //if the user has provided k and R values then use them, else use some default
       char* k_num=argv[1];
        k_neigh=atoi(k_num);
        char* R_num=argv[2];
        R=atoi(R_num);
        } 
    else {
        k_neigh=50;
        R=20;
        a=1;
    }


    vector <vector <float>> query;
    const char* filename2="siftsmall_query.fvecs";
    query =reading_fvecs(filename2,1,100);
    int L_sizelist=100; 
    int medoid_node;
    map <int,list<int>> graph=vamana_index_algorithm(vec,R,medoid_node,L_sizelist,a);
    int s =medoid_node;
    map<int,double> distances;
    pair<set <int>,set <int>> pairset;
    pairset = greedysearch(vec,graph,s,query[0],k_neigh,L_sizelist);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<minutes>(end - start);
    
    cout << "Execution time: " << duration.count() << " minutes" << endl;
    set <int> L=pairset.first;
    cout <<"the k neighbors are: ";
    for(set <int>::iterator k_neighbors =L.begin();k_neighbors!=L.end();k_neighbors++){
        cout <<*k_neighbors<< ",";
    }
    cout <<endl;
}