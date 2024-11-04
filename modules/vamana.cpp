
#include "vamana.h"

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

    //compute pairwise distances once and accumulate them in summ_of_distances
    for (int i = 0; i < number_of_nodes; i++) {
        for (int j = i + 1; j < number_of_nodes; j++) {
            double distance = euclidean_distance(vec[i], vec[j]); //we use squared euclidean distance.(supposed to be faster)
            summ_of_distances[i] += distance;
            summ_of_distances[j] += distance;
        }
    }

    //find the node with the minimum sum of distances
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
//vec contains the dimensions of each node.

map <int, list<int>> vamana_index_algorithm(vector<vector<float>>& vec, int& R,int& medoid_node,int &L_sizelist,double& a,
vector<vector<double>>& vecmatrix){

    int number_of_nodes=vec.size();
    map <int, list<int>> graph = graph_creation(vec,R); //graph that contains each node with its neghbors
     
    medoid_node = medoid(vec);
    cout <<"medoid is" << medoid_node<<"!!!"<<endl;;
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
            
        for(list <int> ::iterator outNeighbors=graph[nodes[i]].begin();outNeighbors!=graph[nodes[i]].end();outNeighbors++){
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
            else{
                graph[*outNeighbors].push_back(nodes[i]);
            }
        }

    }

    return graph;
}

