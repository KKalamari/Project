#include "FilteredGreedySearch.h"


void pickingP(int &p,set <int,DistanceComparator>&L,set<int,DistanceComparator>&V,vector <vector <double>>&querymatrix,int query){
    double mindist=__DBL_MAX__;
    for(auto Lnode : L){
        if (V.find(Lnode) == V.end()){//if the current node is not visited.
            if(mindist>querymatrix[Lnode][query]){
            mindist=querymatrix[Lnode][query];
            p=Lnode;
            }
        }
        }
    }



//function that ensures that L contains at leasτ one node which haven't been already explored.
bool unexplored_nodes(set<int, DistanceComparator>&L,set<int, DistanceComparator>&visited){ 
    
    for(set<int, DistanceComparator> :: iterator lit=L.begin();lit!=L.end();lit++){//for every element there is in L
        bool found=0;
        set<int, DistanceComparator> :: iterator vit=visited.begin(); //we iterate V list
        for(vit=visited.begin();vit!=visited.end();vit++){
        if(*vit==*lit){ //if the current L element exist in V declare found=1 and break the loop, start checking on a new L element
            found=1;
            break;
        }
    }
    if(found==0) //if we didn;t found a match, insantly return 1
        return 1;//just found an unexplored node, return 1
    }
    return 0; //every node has been explored

}

//Distance comparator is defined in the header file of FilteredGreedySearch

pair <vector<int>,vector<int>> FilteredGreedy(map<int,list<int>>&graph,int xq,int knn,int L_sizelist,map <float,int> &M,vector<float>&Fq,vector<vector<double>>& querymatrix,vector<vector<float>>&dataset){
    DistanceComparator comp(querymatrix, xq);
    set<int, DistanceComparator> L(comp); // τα κοντινότερα γειτονικά στοιχεία
    set<int, DistanceComparator> V(comp); // τα επισκέψιμα στοιχεία
    //in our case it will be a singleton set but whatevs
    for(auto filter : Fq){ //because of medoid we already know that they have the same filters.
        int S=M[filter];
        L.insert(S);
    }
    int p;
    // cout<< "The size of V is: "<<V.size()<<endl;
    while (unexplored_nodes(L,V)==1) {
        pickingP(p,L,V,querymatrix,xq); //p<-argmin
        V.insert(p);
        // cout<<"V SIZE IS"<<V.size()<<endl;

        for(auto CandidatesOutNeighbors: graph[p] ){
            
            if ((*(Fq.begin())==dataset[CandidatesOutNeighbors][0]) && (find(V.begin(), V.end(),CandidatesOutNeighbors)==V.end() )) {
                L.insert(CandidatesOutNeighbors);
                // cout<<"I HAVE FOUND NEIGHBORS "<<endl;
            }
        }
        if(knn>0){
        if(L.size()>knn){
            set<int>::iterator Lit=L.begin();
            advance(Lit,knn);
            L.erase(Lit,L.end());
        }
        }
    }
        vector<int> Lvector(L.begin(),L.end());
        vector <int> Vvector(V.begin(),V.end());
        return make_pair(Lvector,Vvector);

    }
    




// while (std::any_of(L.begin(), L.end(), [&V](int node) { return V.find(node) == V.end(); })) {
         //   if (find(Fq.begin(), Fq.end(),dataset[CandidatesOutNeighbors][0])!=Fq.end() && find(V.begin(), V.end(),CandidatesOutNeighbors)==V.end() ) {
