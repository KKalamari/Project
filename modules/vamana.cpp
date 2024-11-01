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


double euclidean_distance(const std::vector<float>& point1, const std::vector<float>& point2) {
    double distance = 0.0;
    for (int k = 0; k < int(point1.size()); k++) {
        distance += pow(point1[k] - point2[k], 2);
    }
    return distance;
}

int medoid(vector<vector<float>>& vec) {
    int number_of_nodes = vec.size();
    vector<double> summ_of_distances(number_of_nodes, 0.0);

    // Compute pairwise distances once and accumulate them in summ_of_distances
    for (int i = 0; i < number_of_nodes; i++) {
        for (int j = i + 1; j < number_of_nodes; j++) {
            double distance = euclidean_distance(vec[i], vec[j]);
            summ_of_distances[i] += distance;
            summ_of_distances[j] += distance;
        }
    }

    // Find the node with the minimum sum of distances
    int returning_node = -1;
    double minimum_distance = numeric_limits<double>::max();
    
    for (int i = 0; i < number_of_nodes; i++) {
        if (summ_of_distances[i] < minimum_distance) {
            minimum_distance = summ_of_distances[i];
            returning_node = i;
        }
    }

    return returning_node;
}

map <int, list<int>> vamana_index_algorithm(vector<vector<float>> vec, int R){
    int number_of_nodes=vec.size();
    map <int, list<int>> graph = graph_creation(vec,R); //graph contains each node with its neghbors
    
    int medoid_node = medoid(vec);
    cout <<"medoid is" << medoid_node<<"!!!"<<endl;;
   // int medoid_node= 8736;
    //creating the random permutation
    //int medoid_node=8736;
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
        pairSet= greedysearch(vec,graph,medoid_node,vec[nodes[i]],1,12);//xσι=vec[nodes[i]],k_neigh,L_sizelist
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

