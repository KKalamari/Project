#include "StitchedVamana.h"

using namespace std;

map<int, set<int>> StitchedVamana(
    vector<vector<float>>& vec,              
    map<float, set<int>>& labels,      
    double alpha,                           
    int Rsmall,                             
    int Lsmall,                             
    int Rstitched,                          
    vector<vector<double>>& vecmatrix        
) {
    map<int, set<int>> finalGraph;          

    for (const auto& [label, nodeSet] : labels) {
        vector<vector<float>> subVec;
        map<int, int> indexMapping; 
        map<int, int> reverseMapping;
        int subIndex = 0;

        for (int node : nodeSet) {
            subVec.push_back(vec[node]);
            indexMapping[subIndex] = node;
            reverseMapping[node] = subIndex;
            subIndex++;
        }

        int medoid = -1; 
        auto subGraph = vamana_index_algorithm(subVec, Rsmall, medoid, Lsmall, alpha, vecmatrix);

        for (const auto& [subNode, neighbors] : subGraph) {
            int originalNode = indexMapping[subNode];
            for (int subNeighbor : neighbors) {
                finalGraph[originalNode].insert(indexMapping[subNeighbor]);
            }
        }
    }

for (auto& [node, neighbors] : finalGraph) {
    int currentNode = node;
    FilteredRobustPrune(finalGraph, currentNode, neighbors, alpha, Rstitched, vecmatrix, vec);
}

    return finalGraph;
}
