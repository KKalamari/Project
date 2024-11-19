#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <set>
#include "FilteredGreedySearch.h"
#include "medoid.h"
#include "FilteredRobust.h"
#include <random>
using namespace std;

map <int,set<int>> FilteredVamanaIndex(vector<vector<double>>&vectormatrix,vector<vector<float>>&DataNodes,double &alpha,int& R,set<float>&category_attributes,map <float,int>&medoids){
    
    map<int,set<int>>graph; //empty graph
    random_device rd; //obtain a random number from hardware
    mt19937 generator(rd()); //seed the generator
    vector<int> randomized_nodes(DataNodes.size());
    iota(randomized_nodes.begin(),randomized_nodes.end(),0);
    shuffle(randomized_nodes.begin(),randomized_nodes.end(),generator);//let σ be a random permutation of n
    int knn=0;
    int L_sizelist=120;
    int counter=0;
    for(auto sigma : randomized_nodes){
        cout<<"I am in the "<<counter << " node";
        counter++;
        vector<float> Filterset={DataNodes[sigma][0]};
        pair <set<pair<double,int>>,set<int>> queuepair;
        queuepair = FilteredGreedy(graph,sigma,knn,L_sizelist,medoids,Filterset,vectormatrix,DataNodes);
        set<int> V=queuepair.second;
       // V.insert(sigma); //PERFORMANCE HIT
        // cout<<"the size of V that goes to robust is:"<<orderedV.size();
        FilteredRobustPrune(graph,sigma,V,alpha,R,vectormatrix,DataNodes);

        for(auto J : graph[sigma]){
            if(int(graph[J].size()+1)>R){
                set<int>JoutN(graph[J].begin(),graph[J].end());
                JoutN.insert(sigma);
                FilteredRobustPrune(graph,J,JoutN,alpha,R,vectormatrix,DataNodes);
            }
            else
                graph[J].insert(sigma);
        }
    }

    return graph;

}