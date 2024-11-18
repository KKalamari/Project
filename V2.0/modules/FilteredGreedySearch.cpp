#include "FilteredGreedySearch.h"


void pickingP(int &p,set <int,DistanceComparator>&L,set<int,DistanceComparator>&V,vector <vector <double>>querymatrix,int query){
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





//Distance comparator is defined in the header file of FilteredGreedySearch

pair <vector<int>,vector<int>> FilteredGreedy(map<int,list<int>>&graph,int xq,int knn,int L_sizelist,map <float,int> &M,vector<float>&Fq,vector<vector<double>> querymatrix,vector<vector<float>>&dataset){
    cout<< " I am inside greedysearch"<<endl;;
    DistanceComparator comp(querymatrix, xq);
    cout << "querymatrix size: " << querymatrix.size() << ", query index: " << xq << endl;
    set<int, DistanceComparator> L(comp); // τα κοντινότερα γειτονικά στοιχεία
    cout <<" I am after L"<<endl;
    set<int, DistanceComparator> V(comp); // τα επισκέψιμα στοιχεία
    cout << " I am after declaring the custom sets"<<endl;
    //in our case it will be a singleton set but whatevs
    for(auto filter : Fq){ //because of medoid we already know that they have the same filters.
        int S=M[filter];
        L.insert(S);
        cout<<"L size now is "<<L.size()<<endl;
    }
    cout << " I am outside of for"<<endl;
    int p;
    while (std::any_of(L.begin(), L.end(), [&V](int node) { return V.find(node) == V.end(); })) {
        pickingP(p,L,V,querymatrix,xq); //p<-argmin
        V.insert(p);
        
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
        vector<int> Lvector(L.begin(),L.end());
        vector <int> Vvector(V.begin(),V.end());
        return make_pair(Lvector,Vvector);

    }
    




