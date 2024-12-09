#include "Robust_ext.h"
using namespace std;





int pickingP(int point, set<int> &candidate_set, vector<vector<double>> &distances)
{
    int p; //the nearest neighbor
    float mindist;//min distance
    auto it = candidate_set.begin();
    advance(it, 1);  //we begin from the second element
    if(*(candidate_set.begin())==point){ //if its the point itselft then go to the next one and get the dist
        
        mindist=distances[point][*it];
        p=*it;
    }
    else{//else just get the dist
        mindist=distances[point][*candidate_set.begin()];
        p=*(candidate_set.begin());
    }
    for( set <int> ::iterator  setIt=it;setIt!=candidate_set.end();setIt++){
        if(distances[*setIt][point]<mindist && *setIt!=point){
            mindist=distances[*setIt][point];
            p=*setIt; //assigning the minimum distance neighbor to p
        }
    }
    return p;
}

//parameters are the random R-graph, point =p of the pseudocode, candidate_set=V,alpha,R, matrix of distances
void RobustPrune(
    map<int,set<int>>& graph,
    int point,
    set<int>& candidateSet, 
    double alpha,
    size_t R,
    vector<vector<double>>&vecmatrix
) {
//adding every neighbor of p in the candidate Set
    for (int neighbor : graph[point]) 
    {  
        if(neighbor!=point)
            candidateSet.insert(neighbor); //inserting all the neighbors of point in the candidate_set
    }
      // there is a possibily that V set contains point as an element which was causing a segmentation problem. When i added this it got fixed!
    set <int>::iterator exisiting_p=candidateSet.find(point);
    if(exisiting_p!=candidateSet.end())
        candidateSet.erase(point);  //V=P/{p}
    graph[point].clear();
    
    
    int p; //p will contain the nearest neighbor.Initialized with -1 to ensure it starts as empty 
    while (candidateSet.empty()!=1 && graph[point].size()<R){
        p=pickingP(point,candidateSet,vecmatrix); //choosing the node from the candidate set with the smallest distance from current point and adressing it to p
       
        graph[point].insert(p);  

        if(graph[point].size()>=R ) 
            break;
        
    
        set <int> nodes_to_be_erased;
        for (auto candidate = candidateSet.begin(); candidate != candidateSet.end(); candidate++ ) {
            if (alpha * vecmatrix[p] [*candidate] <= vecmatrix[point] [*candidate]) {
               nodes_to_be_erased.insert(*candidate);

            }
            }
         
        for(auto nodes_to_delete : nodes_to_be_erased){
            candidateSet.erase(nodes_to_delete);
        }

        }
    }
       

