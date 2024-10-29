#include "robust_ext.h"
#include "euclidean_distance.h"
#include "graph_creation.h"
#include "greedysearch.h"
using namespace std;


int medoid(vector<vector<float>>vec){ //returning the node which is the medoid (the node with the least average distance from every other node)
    int returning_node=-1;
    vector<double>summ_of_distances (vec.size(), 0.0);
    set <pair<double,int>>summ_distances;
    for(int i=0;i<int(vec.size());i++){
        map<int,double>distances;
        euclidean_distance(vec,vec[i],distances);
        for(int j=0;j<int(vec.size());j++){
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

    return returning_node;
}

void vamana_index_algorithm(vector<vector<float>> vec,int L, int R){
    graph_creation(vec,R);
    map <int, list<int>> graph = graph_creation(vec,R);
    int medoid_node =medoid(vec);
    map <int, list<int>> s;
    s[medoid_node]=graph[medoid_node]; //giving the neighbor nodes as value to the s node.
    
}