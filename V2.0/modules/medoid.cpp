#include <iostream>
#include<map>
#include <vector>
#include <list>
#include <set>
#include <random>
#include <algorithm>

using namespace std;

//chooses the node which has been used the least as a starting node
void pfinder(vector <int> &Rf,map<int,float>&T,int &p){
    int min=T[*(Rf.begin())];
    p=*(Rf.begin());
    for(auto Pcandidates : Rf){
        if(T[Pcandidates]<min){
            min=T[Pcandidates];
            p = Pcandidates;
        }
    }
}


map <int,float> FindMedoid(vector<vector<float>>DataNodes,int r,set <float>& category_attributes){
    map<int,float> M;
    map<int,float> T;
    map <float,vector<int>> Pf;//the first int is the filter and the vector is every node with the same filter
    vector <int> Rf; //randomly sampled data point ids from Pf
    random_device rd; //obtain a random number from hardware
    mt19937 generator(rd()); //seed the generator
    int p; //argmin
    int Datasize= DataNodes.size();
    for(auto Filters : category_attributes){ //for every fitler there is
        for(int i=0;i<Datasize;i++){ //we iterate the whole dataset and find nodes with matchign filters
            if(DataNodes[i][0]==Filters);
                Pf[Filters].push_back(i); // Pf will contain every node with matching filter of the current index "Filters"
        }
        Rf=Pf[Filters]; //initializing vector Rf as the vector of all nodes with the specific filter index.
        shuffle(Rf.begin(),Rf.end(),generator); //randomizing rf
       
        while(Rf.size()>r) // we only need r randomly sampled data points
            Rf.pop_back();
        
        pfinder(Rf,T,p);
        M[Filters]=p;
        T[p]++; // T[p]<-T[p]+1

    }
    return M;
}