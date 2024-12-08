#include "Vamana.h"
#include "GreedySearch.h"
#include "Robust_ext.h"


map<int, set<int>> graph_creation(list<int>& labeled_nodes, int R) {
    int labeled_size = labeled_nodes.size();
    cout << "The vector size is: " << labeled_nodes.size() << "\n";

    map<int, set<int>> adj;
    // vector<int> nodes_vector(labeled_nodes.begin(), labeled_nodes.end());
    srand(time(0));
    if(labeled_size>1){
        for (int node : labeled_nodes) {
            int neighbors_added = 0;
            list<int> remaining_neighbors = labeled_nodes;
            remaining_neighbors.remove(node); //erasing the node from the candidates neighbors so a node can't have its self for a neighbor
            while (neighbors_added < R ) {
                
                //picking randomly a neighbor which has not been assigned as of yet(that's why we use remaining_neighbors)
                int random_index = rand() % remaining_neighbors.size();
                auto it = remaining_neighbors.begin();
                advance(it, random_index);
                int random_neighbor = *(it);

                //ensuring
                if (random_neighbor != node && adj[node].find(random_neighbor) == adj[node].end()) {
                    adj[node].insert(random_neighbor);
                    remaining_neighbors.erase(it);
                    neighbors_added++;
                }
                if(remaining_neighbors.empty()) 
                    break;
            }
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
    int medoid_node = M[filters];
   save_graph_to_binary_set(graph, "graph_data.bin");
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
        RobustPrune(graph,nodes[i],setV,a,R_small,vecmatrix);
            
        //if a node exceeds the R limit while making a node directed
        //then fill a set with the nodes of its neighbors + the extra one we  want to add
        //and call robust prune.
        for(set <int> ::iterator outNeighbors=graph[nodes[i]].begin();outNeighbors!=graph[nodes[i]].end();outNeighbors++){
            if(int(graph[*outNeighbors].size())+1>R_small){
                setV.clear(); 
                setV.insert(i);
                for(auto neighbors : graph[*outNeighbors]){
                    if(*outNeighbors==i)
                        continue;
                    setV.insert(neighbors);
                    
                }
                
                RobustPrune(graph,*outNeighbors,setV,a,R_small,vecmatrix);

            }
            else{ //else just add the extra neighbor
                graph[*outNeighbors].insert(nodes[i]);
            }
        }

    }

    return graph;
}