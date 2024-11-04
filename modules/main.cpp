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
        k_neigh=100;
        R=16;
        a=1.1;
    }


    vector <vector <float>> queries;

    
    const char* filename2="siftsmall_query.fvecs";
    queries =reading_fvecs(filename2,1,100);
    int vector_number = int (vec.size());
    int query_number = int (queries.size());

    vector<vector<double>> vecmatrix(vector_number,vector<double>(vector_number));  //10000 *10000 matrix for the euclidean distance of every node between every node
    vector <vector <double>> querymatrix(vector_number,vector<double>(query_number)); // 10000 *100 matrix which calculates the euclidean distance between database node and queries
    cout <<"the matrix size is:"<<vecmatrix.size() <<endl;
    euclidean_distance_of_database(vec,vecmatrix); //calculating the euclidean distances of the whole database of nodes with each other
    cout<<"I am after calculating database "<< endl;
    euclidean_distance_of_queries (vec,queries,querymatrix); //cal

    cout <<"I am aftet the calculation"<<endl;
    int L_sizelist=150; 
    int medoid_node;
    map <int,list<int>> graph=vamana_index_algorithm(vec,R,medoid_node,L_sizelist,a,vecmatrix,querymatrix);
    int s =medoid_node;
    map<int,double> distances;
    vector <vector <int>> ground;
    const char* filename3 = "siftsmall_groundtruth.ivecs";
    ground = reading_ivecs (filename3,1,100);
    int k =0;
    for(int i =0; i<100; i++) {
        vector<int> comp = ground[i];
        pair<set <int>, set<int>> L = greedysearch (vec,graph,s,i,k_neigh,L_sizelist,querymatrix);
        set <int> setV = L.first;
        int count = 0 ;
        for(const float& value : comp) {
            if(setV.count(value) > 0)
            count++;
        }
        if (count>= 90) 
            k++;
        cout<<count<<endl;
    }
    cout<< k<< endl;
    int i=0;
    pair<set <int>,set <int>> pairset = greedysearch(vec,graph,s,i,k_neigh,L_sizelist,querymatrix);
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