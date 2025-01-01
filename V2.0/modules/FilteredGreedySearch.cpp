#include "FilteredGreedySearch.h"
#include <limits>
#include <chrono>

//function that ensures that L contains at leasτ one node which haven't been already explored.
bool unexplored_nodes(const set<pair<double, int>>& L, const set<int>& visited) { 
    for (const auto& elem : L) { // Iterate through each element in L
        if (visited.find(elem.second) == visited.end()) {
            return true; // Found an unexplored node
        }
    }
    return false; // All nodes in L have been explored
}



pair <set<pair<double,int>>,set<int>> FilteredGreedy(map<int,set<int>>&graph,int xq,int knn,int L_sizelist,map <float,int> &M,vector<float>&Fq,vector<vector<double>>& querymatrix,vector<vector<float>>&dataset,
set <float> &category_attributes){
    auto starting_time =std::chrono::system_clock::now();
    set<pair<double,int>> L; //L set is going to be ordered by the euclidean distance
    set <int> V;
    pair<double,int>node; //nodes to be inserted in L set.

    if(Fq[0]==-1){ //if it's an unfiltered query we pass every medoid(which is actually the closest node of the filter) to L
        for(auto& filter : category_attributes){ //because of medoid we already know that they have the same filters.
        int S=M[filter];
        pair<double,int>node= make_pair(querymatrix[S][xq],S);

        L.insert(node);
        }
    }
    else{
        for(auto& filter : Fq){ //because of medoid we already know that they have the same filters.
            int S=M[filter];
            pair<double,int>node= make_pair(querymatrix[S][xq],S);

            L.insert(node);
        }
    }
    int p;
    while (unexplored_nodes(L,V)==1) {
        // pickingP(p,L,V,querymatrix,xq); //p<-argmin
        for(auto& candidateP: L){
            if((V.find(candidateP.second)==V.end())==1){
                p=candidateP.second;
                break;
            }
        }
        V.insert(p);
        for(auto& CandidatesOutNeighbors: graph[p] ){
            if ((*(Fq.begin())==dataset[CandidatesOutNeighbors][0] || *(Fq.begin())==-1.0) && (V.find(CandidatesOutNeighbors)==V.end() )) {
                node=make_pair(querymatrix[CandidatesOutNeighbors][xq],CandidatesOutNeighbors);
                L.insert(node);
            }
            
        }
        
        if(L.size()>L_sizelist){
            set<pair<double,int>>::iterator Lit=L.begin();
            advance(Lit,L_sizelist);
            L.erase(Lit,L.end()); //deleting the last nodes when L-sizelist threshold is exceeded.
        }
    }

    if(knn>0){
        if(L.size()>knn){
            set<pair<double,int>>::iterator Lit=L.begin();
            advance(Lit,knn);
            L.erase(Lit,L.end());
        }
        }
        auto end =std:: chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - starting_time;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    //    cout << " elapsed time in greedy search: " << elapsed_seconds.count()<<endl;
        return make_pair(L,V);

    }
    

















