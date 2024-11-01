#include "robust_ext.h"
#include "euclidean_distance.h"
#include "graph_creation.h"
#include "greedysearch.h"
#include <unordered_set>
#include "vamana.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <set>
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

            summ_of_distances[i]+=distances[j];
            summ_of_distances[j]+=distances[i];
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

map <int, list<int>> vamana_index_algorithm(vector<vector<float>> vec, int R){
    int number_of_nodes=vec.size();
    map <int, list<int>> graph = graph_creation(vec,R); //graph contains each node with its neghbors
    
    //int medoid_node = medoid(vec);
   // int medoid_node= 8736;
    //creating the random permutation
    int medoid_node=8736;
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
        pairSet= greedysearch(vec,graph,medoid_node,vec[nodes[i]],1,12,distances);//xσι=vec[nodes[i]],k_neigh,L_sizelist
        set <int>  setV= pairSet.second;
        RobustPrune(graph,nodes[i],vec,setV,1.2,12);  //12=R,σ(ι)=nodes[i]
            
        for(list <int> ::iterator outNeighbors=graph[nodes[i]].begin();outNeighbors!=graph[nodes[i]].end();outNeighbors++){
            if(int(graph[*outNeighbors].size())+1>R){
                setV.clear();
                for(auto neighbors : graph[*outNeighbors]){
                    if(*outNeighbors==i)
                        continue;
                    setV.insert(neighbors);
                    
                }
                
                RobustPrune(graph,*outNeighbors,vec,setV,1,12);

            }
            else{
                graph[*outNeighbors].push_back(nodes[i]);
            }
        }

    }

    cout<< "Final graph: "<<endl;
    for(int i=0;i<int(graph.size());i++){
        cout <<" node "<< i<< " has neighbors:";
        for(auto final_nodes : graph[i] ){
            cout << final_nodes <<" ";
        }
    }
    



    cout <<endl;
    return graph;
}

