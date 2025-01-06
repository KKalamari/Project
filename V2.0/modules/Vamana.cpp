#include "Vamana.h"
#include "GreedySearch.h"
#include "Robust_ext.h"
#include <chrono>
#include <omp.h>

map<int, set<int>> graph_creation(list<int>& labeled_nodes, int R) {
    int count=4;
    int labeled_size = labeled_nodes.size();
    map<int, set<int>> adj;
    
    if (labeled_size > 1) {
        // Convert list to vector for better parallel access
        vector<int> nodes_vector(labeled_nodes.begin(), labeled_nodes.end());
        
        // Create a mutex for protecting the shared adj map
      //  #pragma omp parallel num_threads(count)
        {
            // Create thread-local random number generator
            random_device rd;
            mt19937 gen(rd());
            
            for (int i = 0; i < nodes_vector.size(); i++) {
                int node = nodes_vector[i];
                int neighbors_added = 0;
                
                // Create thread-local copy of remaining neighbors
                vector<int> remaining_neighbors(nodes_vector);
                remaining_neighbors.erase(
                    remove(remaining_neighbors.begin(), remaining_neighbors.end(), node),
                    remaining_neighbors.end()
                );
                
                set<int> local_neighbors;
                
                while (neighbors_added < R && !remaining_neighbors.empty()) {
                    uniform_int_distribution<> dis(0, remaining_neighbors.size() - 1);
                    int random_index = dis(gen);
                    int random_neighbor = remaining_neighbors[random_index];
                    
                    if (local_neighbors.find(random_neighbor) == local_neighbors.end()) {
                        local_neighbors.insert(random_neighbor);
                        remaining_neighbors.erase(
                            remaining_neighbors.begin() + random_index
                        );
                        neighbors_added++;
                    }
                }
                
                // Critical section: update the shared adj map
                // #pragma omp critical
                // {
                    adj[node] = local_neighbors;
                //}
            }
        }
    }
    return adj;
}





map <int, set<int>> vamana_index_algorithm(map<float,list<int>>&labeled_nodes,float filters,double a,int& R_small,int &L_small,
vector<vector<double>>& vecmatrix,
map<float,int> M,int R_stitched){
    // cout<<"doing the "<<filters<<"iteration";
    int number_of_nodes=labeled_nodes[filters].size();
    auto time_before =chrono::system_clock::now();
    map <int, set<int>> graph = graph_creation(labeled_nodes[filters],R_small); //graph that contains each node with its neghbors
    // auto time_now = chrono::system_clock::now();
    // chrono::duration <double> elapsed = time_now - time_before;
    // cout<<"the elapsed time for graph creation is:" <<elapsed.count()<<endl;
    int medoid_node = M[filters];
   //save_graph_to_binary_set(graph, "graph_data.bin");
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
        pair <set<pair<double,int>>,set<int>> pairSet;
        int k=1;
        // time_before = chrono:: system_clock::now();
        pairSet= greedysearch(graph,medoid_node,nodes[i],k,L_small,vecmatrix);
        set <int>  setV= pairSet.second;
        // time_now = chrono:: system_clock::now();
        // chrono::duration<double> elapsed_time = time_now - time_before;
        RobustPrune(graph,nodes[i],setV,a,R_stitched,vecmatrix);
        
        // time_now = chrono::system_clock::now();
        // chrono::duration<double> elapsed_time = time_now - time_before;
        // cout<<"the time for Robust is"<<elapsed.count()<<endl;
            
        //if a node exceeds the R limit while making a node directed
        //then fill a set with the nodes of its neighbors + the extra one we  want to add
        //and call robust prune.
        for(set <int> ::iterator outNeighbors=graph[nodes[i]].begin();outNeighbors!=graph[nodes[i]].end();outNeighbors++){
            if(int(graph[*outNeighbors].size())+1>R_stitched){
                setV.clear(); 
                setV.insert(i);
                for(auto neighbors : graph[*outNeighbors]){
                    if(*outNeighbors==i)
                        continue;
                    setV.insert(neighbors);
                    
                }
                
                RobustPrune(graph,*outNeighbors,setV,a,R_stitched,vecmatrix);

            }
            else{ //else just add the extra neighbor
                graph[*outNeighbors].insert(nodes[i]);
            }
        }

    }

    return graph;
}