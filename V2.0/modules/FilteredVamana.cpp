#include <iostream>
#include <map>
#include <list>
#include <vector>
#include<set>
#include "FilteredGreedySearch.h"
#include "medoid.h"
#include "FilteredRobust.h"
#include <random>
using namespace std;

map <int,list<int>> FilteredVamanaIndex(vector<vector<double>>&vectormatrix,vector<vector<float>>&DataNodes,int &alpha,int& R,set<float>&category_attributes){
    
    map<int,list<int>>graph; //empty graph
    map <float,int> medoids=FindMedoid(DataNodes,R,category_attributes);//return a map with every key being the filter and the value being the staring node
    random_device rd; //obtain a random number from hardware
    mt19937 generator(rd()); //seed the generator
    vector<int> randomized_nodes(DataNodes.size());
    iota(randomized_nodes.begin(),randomized_nodes.end(),0);
    shuffle(randomized_nodes.begin(),randomized_nodes.end(),generator);//let σ be a random permutation of n
    int knn=1;
    int L_sizelist=120;
    for(auto sigma : randomized_nodes){
        cout<<"sigma is currently "<<sigma << endl;
        DistanceComparator comp(vectormatrix, sigma);
        vector<float> Filterset={DataNodes[sigma][0]};
        pair <vector<int>,vector<int>>queuepair;
        queuepair = FilteredGreedy(graph,sigma,knn,L_sizelist,medoids,Filterset,vectormatrix,DataNodes);
        //DistanceComparator comp(vectormatrix, sigma);
        vector<int> V=queuepair.second;
        V.emplace(V.begin(),sigma); //PERFORMANCE HIT
        set<int,DistanceComparator>orderedV(V.begin(),V.end(),comp);
        FilteredRobustPrune(graph,sigma,orderedV,alpha,R,vectormatrix,DataNodes);

        for(auto J : graph[sigma]){
            graph[J].push_back(sigma);
            if(int(graph[sigma].size())>R){
                set<int,DistanceComparator>JoutN(graph[J].begin(),graph[J].end(),comp);
                FilteredRobustPrune(graph,J,JoutN,alpha,R,vectormatrix,DataNodes);
            }
        }
    }

    return graph;

}