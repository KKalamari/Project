#include <iostream>
#include<vector>
#include "reading.h"
#include "graph_creation.h"
#include "greedysearch.h"
#include "euclidean_distance.h"
#include <list>
#include <utility>
using namespace std;
// the syntax for execution  is: ./main k_num R_num

int main(int argc,char** argv){
    const char* filename="sift_base.fvecs";
    vector<vector<float>>* vec=new vector<vector<float>>; //structure where we gonna keep all the vectors from the dataset file
    vec=reading_fvecs(filename,1,1000000);  
    int k_neigh; //the k nearest neighbors we want to find.
    int R; //The number which defines the random neighbors each node is going to have
    if(argc>1){ //if the user has provided k and R values then use them, else use some default
       char* k_num=argv[1];
        k_neigh=atoi(k_num);
        char* R_num=argv[2];
        R=atoi(R_num);
        } 
    else {
        k_neigh=20;
        R=7;
    }
    int L_sizelist=k_neigh; 
    vector<float> xq;
    filename="sift_query.fvecs";
    vector<vector<float>>* vec2=new vector<vector<float>>; //structure where we gonna keep all the vectors from the dataset file
    vec2=reading_fvecs(filename,1,5);
    cout <<"reading got done"<< endl;
    xq=(*vec2)[0]; //we assing the query as the first vector
       
    map <int, set<int>> graph;
    graph = graph_creation(vec,R);
    cout <<"graph got made"<< endl;
    map  <int,float> distances;
    cout << " I am before the calculation"<<endl;
    euclidean_distance(vec,xq,distances); //inside this function the distances variable is filled with the euclidean_distances of every vector from the query point
    cout <<"I am before the greedySearch LESGOO"<<endl;
    pair <set <int>,set <int>> PairSet;
    PairSet = greedysearch(graph,xq,k_neigh,L_sizelist,distances);
    set <int> L=PairSet.first;
    set <int> V=PairSet.second;
    cout<< "the L set is: "<< endl;
    for(set <int> :: iterator lit=L.begin() ;lit!=L.end();lit++){
        cout<< " "<<*lit;
    }
    cout <<endl << "I am before deallocating"<< endl;

    
    delete vec;
    delete vec2;
}
