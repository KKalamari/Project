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
// the syntax for execution  is: ./main k_num R_num a_num l_num

int main(int argc,char** argv){
    auto start = high_resolution_clock::now();
    const char* filename="siftsmall_base.fvecs";
    vector<vector<float>> vec; //structure where we gonna keep all the vectors from the dataset file
    vec=reading_fvecs(filename,1,10000);  
    int k_neigh = 100; //the k nearest neighbors we want to find.
    int R = 16; //The number which defines the random neighbors each node is going to have
    double a=1.1;
    int L_sizelist=150;
    if(argc>1) //if the user has provided k and R values then use them, else use some default
        k_neigh= atoi(argv[1]);
    if(argc>2) 
        R = atoi(argv[2]);
    if(argc>3)
        a = atof(argv[3]);
    if(argc>4) 
        L_sizelist = atoi(argv[4]);           

    cout<<" k is "<< k_neigh <<"\n R is "<<R<<"\n a is " <<a <<endl<<" L is " <<L_sizelist<<endl; 
    vector <vector <float>> queries;

    
    const char* filename2="siftsmall_query.fvecs";
    queries =reading_fvecs(filename2,1,100);
    int vector_number = int (vec.size());
    int query_number = int (queries.size());

    vector<vector<double>> vecmatrix(vector_number,vector<double>(vector_number));  //10000 *10000 matrix for the euclidean distance of every node between every node
    vector <vector <double>> querymatrix(vector_number,vector<double>(query_number)); // 10000 *100 matrix which calculates the euclidean distance between database node and queries
    euclidean_distance_of_database(vec,vecmatrix); //calculating the euclidean distances of the whole database of nodes with each other
    euclidean_distance_of_queries (vec,queries,querymatrix); //cal


    int medoid_node;
    map <int,list<int>> graph=vamana_index_algorithm(vec,R,medoid_node,L_sizelist,a,vecmatrix);
    cout <<"right after gre[h creatong"<<endl;
    int s =medoid_node;
    map<int,double> distances;
    vector <vector <int>> ground;
    const char* filename3 = "siftsmall_groundtruth.ivecs";
    ground = reading_ivecs (filename3,1,100);
    int k =0;
    for(int i =0; i<100; i++) { //testing all the queries to see how much accuracy we have
        vector<int> comp = ground[i];
        pair<set <int>, set<int>> L = greedysearch (graph,s,i,k_neigh,L_sizelist,querymatrix);
        set <int> setV = L.first;
        int count = 0 ;
        for(const int& value : comp) {
            if(setV.count(value) > 0)
            count++;
        }
        if (count>= 90) 
            k++;
        cout<<count<<endl;
    }
    cout<< k<< endl;
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<minutes>(end - start);
    
    cout << "Execution time: " << duration.count() << " minutes" << endl;

}