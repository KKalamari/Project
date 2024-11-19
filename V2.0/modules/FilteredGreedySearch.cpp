#include "FilteredGreedySearch.h"


void pickingP(int &p,set <pair<double,int>>&L,set<int>&V,vector <vector <double>>&querymatrix,int query){
    double mindist=std::numeric_limits<double>::max();
    for(auto Lnode : L){
        if (V.find(Lnode.second) == V.end()){//if the current node is not visited.
            if(mindist>querymatrix[Lnode.second][query]){
            mindist=querymatrix[Lnode.second][query];
            p=Lnode.second;
            }
        }
        }
    }



//function that ensures that L contains at leasτ one node which haven't been already explored.
bool unexplored_nodes(const set<pair<double, int>>& L, const set<int>& visited) { 
    for (const auto& elem : L) { // Iterate through each element in L
        if (visited.find(elem.second) == visited.end()) {
            return true; // Found an unexplored node
        }
    }
    return false; // All nodes in L have been explored
}


//Distance comparator is defined in the header file of FilteredGreedySearch

pair <set<pair<double,int>>,set<int>> FilteredGreedy(map<int,list<int>>&graph,int xq,int knn,int L_sizelist,map <float,int> &M,vector<float>&Fq,vector<vector<double>>& querymatrix,vector<vector<float>>&dataset){
    set<pair<double,int>> L; //L set is going to be ordered by the euclidean distance
    set <int> V;
    pair<double,int>node; //nodes to be inserted in L set.
    //in our case it will be a singleton set but whatevs
    for(auto filter : Fq){ //because of medoid we already know that they have the same filters.
        int S=M[filter];
        pair<double,int>node= make_pair(querymatrix[S][xq],S);
        L.insert(node);
    }
    int p;
    // cout<< "The size of V is: "<<V.size()<<endl;
    while (unexplored_nodes(L,V)==1) {
        pickingP(p,L,V,querymatrix,xq); //p<-argmin
        V.insert(p);
        // cout<<"V SIZE IS"<<V.size()<<endl;

        for(auto CandidatesOutNeighbors: graph[p] ){
            
            if ((*(Fq.begin())==dataset[CandidatesOutNeighbors][0]) && (find(V.begin(), V.end(),CandidatesOutNeighbors)==V.end() )) {
                node=make_pair(querymatrix[CandidatesOutNeighbors][xq],CandidatesOutNeighbors);
                L.insert(node);
                // cout<<"I HAVE FOUND NEIGHBORS "<<endl;
            }
        }
        if(knn>0){
        if(L.size()>knn){
            set<pair<double,int>>::iterator Lit=L.begin();
            advance(Lit,knn);
            L.erase(Lit,L.end());
        }
        }
    }
       
        return make_pair(L,V);

    }
    




// while (std::any_of(L.begin(), L.end(), [&V](int node) { return V.find(node) == V.end(); })) {
         //   if (find(Fq.begin(), Fq.end(),dataset[CandidatesOutNeighbors][0])!=Fq.end() && find(V.begin(), V.end(),CandidatesOutNeighbors)==V.end() ) {
