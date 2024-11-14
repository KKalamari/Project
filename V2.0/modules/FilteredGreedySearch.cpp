#include "FilteredGreedySearch.h"


void pickingP(int &p,set <int,DistanceComparator>&L,set<int,DistanceComparator>&V,vector <vector <double>>querymatrix,int query){
    double mindist=__DBL_MAX__;
    for(auto Lnode : L){
        if (find(V.begin(), V.end(),Lnode)==V.end()) //if the current node is not visited.
                p=Lnode;
        }
    }


//Distance comparator is defined in the header file of FilteredGreedySearch

pair <vector<int>,vector<int>> FilteredGreedy(map<int,vector<int>>&graph,int xq,int knn,int L_sizelist,map <float,int> &M,vector<float>&Fq,vector<vector<double>> querymatrix,vector<vector<float>>&dataset){
    DistanceComparator comp(querymatrix, xq);
    set<int, DistanceComparator> L(comp); // τα κοντινότερα γειτονικά στοιχεία
    set<int, DistanceComparator> V(comp); // τα επισκέψιμα στοιχεία
    //in our case it will be a singleton set but whatevs
    for(auto filter : Fq){ //because of medoid we already know that they have the same filters.
        int S=M[filter];
        L.insert(S);
    }
    int p;
    while(search(V.begin(),V.end(),L.begin(),L.end())==V.end()){ //L is not a subsequence of V, thus there is at least one unvisited node
    pickingP(p,L,V,querymatrix,xq); //p<-argmin
    V.insert(p);
    if(graph.size()==0){
    
        for(int i=0;i<int(dataset.size());i++){
            if (find(Fq.begin(), Fq.end(),dataset[i][0])!=Fq.end()){ //if the specific i node has the same filter as the query then
                V.insert(i);
            }
        }
        if(L.size()>L_sizelist){
            set<int>::iterator Lit=L.begin();
            advance(Lit,L_sizelist);
            L.erase(Lit,L.end());
            Lit=L.begin();
            V.insert(Lit,L.end());
        }
    }

    else{
        cout<<"P is "<< p <<endl;
        for(auto CandidatesOutNeighbors: graph[p] ){
            if (find(Fq.begin(), Fq.end(),dataset[CandidatesOutNeighbors][0])!=Fq.end() && find(V.begin(), V.end(),CandidatesOutNeighbors)==V.end() ) {
                L.insert(CandidatesOutNeighbors);
            }
        }
        if(L.size()>L_sizelist){
            set<int>::iterator Lit=L.begin();
            advance(Lit,L_sizelist);
            L.erase(Lit,L.end());
            Lit=L.begin();
        }
    }
    }
    vector <int> Lvector(L.begin(),L.end());
    vector<int> Vvector(V.begin(),V.end());

    return make_pair(Lvector,Vvector);

}   




