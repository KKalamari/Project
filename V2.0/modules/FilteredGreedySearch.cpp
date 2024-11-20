#include "FilteredGreedySearch.h"
#include <limits>
#include <chrono>
// void pickingP(int &p,set <pair<double,int>>&L,set<int>&V,vector <vector <double>>&querymatrix,int query){
//     double mindist=std::numeric_limits<double>::max();
//     for(auto Lnode : L){
//         if (V.find(Lnode.second) == V.end()){//if the current node is not visited.
//             if(mindist>querymatrix[Lnode.second][query]){
//             mindist=querymatrix[Lnode.second][query];
//             p=Lnode.second;
//             }
//         }
//         }
//     }



//function that ensures that L contains at leasτ one node which haven't been already explored.
bool unexplored_nodes(const set<pair<double, int>>& L, const set<int>& visited) { 
    for (const auto& elem : L) { // Iterate through each element in L
        if (visited.find(elem.second) == visited.end()) {
            return true; // Found an unexplored node
        }
    }
    return false; // All nodes in L have been explored
}



pair <set<pair<double,int>>,set<int>> FilteredGreedy(map<int,set<int>>&graph,int xq,int knn,int L_sizelist,map <float,int> &M,vector<float>&Fq,vector<vector<double>>& querymatrix,vector<vector<float>>&dataset){
    auto starting_time =std::chrono::system_clock::now();
    set<pair<double,int>> L; //L set is going to be ordered by the euclidean distance
    set <int> V;
    pair<double,int>node; //nodes to be inserted in L set.
    //in our case it will be a singleton set but whatevs
    for(auto& filter : Fq){ //because of medoid we already know that they have the same filters.
        int S=M[filter];
        pair<double,int>node= make_pair(querymatrix[S][xq],S);

        L.insert(node);
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
            if ((*(Fq.begin())==dataset[CandidatesOutNeighbors][0]) && (V.find(CandidatesOutNeighbors)==V.end() )) {
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
        cout<<"I AM REACHING MY LIMITSSSSS!!!!!!!!!!!!!!!!!"<<endl;
        cout<<"the L size is:"<<L.size()<<endl;
        if(L.size()>knn){
            set<pair<double,int>>::iterator Lit=L.begin();
            advance(Lit,knn);
            L.erase(Lit,L.end());
        }
        }
        auto end =std:: chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - starting_time;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
       cout << " elapsed time in greedy search: " << elapsed_seconds.count()<<endl;
        return make_pair(L,V);

    }
    




// while (std::any_of(L.begin(), L.end(), [&V](int node) { return V.find(node) == V.end(); })) {
         //   if (find(Fq.begin(), Fq.end(),dataset[CandidatesOutNeighbors][0])!=Fq.end() && find(V.begin(), V.end(),CandidatesOutNeighbors)==V.end() ) {
