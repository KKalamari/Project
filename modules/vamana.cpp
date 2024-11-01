#include "robust_ext.h"
#include "euclidean_distance.h"
#include "graph_creation.h"
#include "greedysearch.h"
#include <unordered_set>
#include "vamana.h"
#include <algorithm>
#include <random>
#include <iostream>
using namespace std;


int medoid(vector<vector<float>>vec){ //returning the node which is the medoid (the node with the least average distance from every other node)
    int returning_node=-1;
    int number_of_nodes=vec.size();
    vector<double>summ_of_distances (number_of_nodes, 0.0);
    set <pair<double,int>>summ_distances;
    for(int i=0;i<int(number_of_nodes);i++){
        map<int,double>distances;
        euclidean_distance(vec,vec[i],distances);
        for(int j=0;j<int(number_of_nodes);j++){
            // if(i==j)
            //     continue;
           // cout << " "<<distances[j]<<endl;
            summ_of_distances[i]+=distances[j];
        }
    }
   
    double minimum=summ_of_distances[0];
    int j=0;
    returning_node =0;
    for(auto i :summ_of_distances){
       
        if (i<minimum){
            minimum=i;
            returning_node =j;
            
        }
        j++;
    }

    cout<< "the medoid is "<<returning_node<< " with distance " <<summ_of_distances[returning_node]<<endl;
    return returning_node;
}

void vamana_index_algorithm(vector<vector<float>> vec, int R){
    int number_of_nodes=vec.size();
    map <int, list<int>> graph = graph_creation(vec,R); //graph contains each node with its neghbors
    int medoid_node = medoid(vec);

    //creating the random permutation
    random_device rd; // Obtain a random number from hardware
    mt19937 generator(rd()); // Seed the generator
    vector<int> nodes;
    for(int i=0;i<int(number_of_nodes);i++){
        nodes.push_back(i);
    }
    shuffle(nodes.begin(),nodes.end(),generator); //random permutation of graph's nodes
    map <int,double>distances;
    for(int i=0;i<number_of_nodes;i++){
        pair < set<int>,set<int>> pairSet;
        pairSet= greedysearch(graph,medoid_node,vec[nodes[i]],1,10,distances);//xσι=vec[nodes[i]],k_neigh,L_sizelist
        set <int> V= pairSet.second;
        RobustPrune(graph,nodes[i],vec,V,1,12);  //12=R,σ(ι)=nodes[i]
        for(set <int> ::iterator outNeighbors=V.begin();outNeighbors!=V.end();outNeighbors++){
            bool already_existing=0;

            if(int(graph[*outNeighbors].size())+1>R){
                
                V.clear();
                for(auto neighbors : graph[*outNeighbors]){
                    V.insert(neighbors);
                    if(neighbors==i)
                        already_existing=1;
                }

                if(already_existing==0)
                    V.insert(i);

                RobustPrune(graph,*outNeighbors,vec,V,1,12);
            }
            else{
                graph[*outNeighbors].push_back(nodes[i]);
            }
        }

    }
    


    cout <<endl;
    
}

