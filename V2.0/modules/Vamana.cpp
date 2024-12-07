#include "Vamana.h"
#include "GreedySearch.h"
#include "Robust_ext.h"

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

map<int, set<int>> graph_creation(list<int>& labeled_nodes, int R) {
    cout << "The vector size is: " << labeled_nodes.size() << "\n";

    map<int, set<int>> adj;
    vector<int> nodes_vector(labeled_nodes.begin(), labeled_nodes.end());
    srand(time(0));

    for (int node : labeled_nodes) {
        int neighbors_added = 0;
        int max_attempts = 100; // Limit to prevent infinite loop
        int attempts = 0;

        while (neighbors_added < R && attempts < max_attempts) {
            attempts++;

            if (nodes_vector.size() <= 1) 
                break; // No valid neighbors possible.

            int random_index = rand() % nodes_vector.size();
            int random_neighbor = nodes_vector[random_index];

            if (random_neighbor != node && adj[node].find(random_neighbor) == adj[node].end()) {
                adj[node].insert(random_neighbor);
                neighbors_added++;
            }
        }

        // If we can't find enough unique neighbors, just stop early.
        if (neighbors_added < R) {
            cout << "Warning: Could not assign " << R << " neighbors to node " << node 
                 << ". Assigned " << neighbors_added << " neighbors.\n";
        }
    }

    return adj;
}





map <int, set<int>> vamana_index_algorithm(map<float,list<int>>&labeled_nodes,float filters,double a,int& R_small,int &L_small,
vector<vector<double>>& vecmatrix,
map<float,int> M,int R,int L_sizelist){
    cout<<"doing the "<<filters<<"iteration";
    int number_of_nodes=labeled_nodes[filters].size();
    map <int, set<int>> graph = graph_creation(labeled_nodes[filters],R_small); //graph that contains each node with its neghbors
    //save_graph_to_binary(graph, "graph_data.bin");
    int medoid_node = M[filters];
   
    //creating the random permutation
    random_device rd; //obtain a random number from hardware
    mt19937 generator(rd()); //seed the generator
    vector<int> nodes;
    for(int i=0;i<int(number_of_nodes);i++){
        nodes.push_back(i);
    }
    shuffle(nodes.begin(),nodes.end(),generator); //random permutation of graph's nodes
    map <int,double>distances;
    for(int i=0;i<number_of_nodes;i++){
        pair < set<int>,set<int>> pairSet;
        int k=1;
        pairSet= greedysearch(graph,medoid_node,nodes[i],k,L_sizelist,vecmatrix);
        set <int>  setV= pairSet.second;
        RobustPrune(graph,nodes[i],setV,a,R,vecmatrix);
            
        //if a node exceeds the R limit while making a node directed
        //then fill a set with the nodes of its neighbors + the extra one we  want to add
        //and call robust prune.
        for(set <int> ::iterator outNeighbors=graph[nodes[i]].begin();outNeighbors!=graph[nodes[i]].end();outNeighbors++){
            if(int(graph[*outNeighbors].size())+1>R){
                setV.clear(); 
                setV.insert(i);
                for(auto neighbors : graph[*outNeighbors]){
                    if(*outNeighbors==i)
                        continue;
                    setV.insert(neighbors);
                    
                }
                
                RobustPrune(graph,*outNeighbors,setV,a,R,vecmatrix);

            }
            else{ //else just add the extra neighbor
                graph[*outNeighbors].insert(nodes[i]);
            }
        }

    }

    return graph;
}