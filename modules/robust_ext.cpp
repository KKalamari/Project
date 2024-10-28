#include "robust_ext.h"
#include <cmath>
#include <iostream>
#include <set>
#include "greedysearch.h"
using namespace std;

using namespace std;


void euclidean_distance(set <int> candidate_set, int point,vector<vector<float>>vec,map<pair <int,int>,float>&distances) 
{
   
    for(set <int> ::iterator setIt=candidate_set.begin();setIt!=candidate_set.end();setIt++){
         double euclidean=0.0;
        for(int i=0;i<int(vec[*setIt].size());i++)
            euclidean+=pow(vec[*setIt][i] - vec[point][i], 2);
    
        distances[make_pair(*setIt,point)]=sqrt(euclidean);
        distances[make_pair(point,*setIt)]=sqrt(euclidean);
    }


}

int pickingP(int point,set <int> candidate_set,map<pair <int,int>,float> &distances ){
    int p;
    float mindist=distances[make_pair(point,*(candidate_set.begin()))];
    cout <<"I am checking "<<point<<","<<*(candidate_set.begin())<<"and the distance is: "<< mindist<<endl;
    p=*(candidate_set.begin());
    for( set <int> ::iterator  setIt=candidate_set.begin();setIt!=candidate_set.end();setIt++){
        cout <<"I am checking "<<point<<","<<*setIt<<"and the distance is: "<<distances[make_pair(*setIt,point)]<<endl;
        if(distances[make_pair(*setIt,point)]<mindist){
            mindist=distances[make_pair(*setIt,point)];
            p=*setIt; //assigning the minimum distance neighbor to p
        }
    }
    return p;
    }

void RobustPrune(
    map<int,list<int>>& graph,
    int point,
    vector<vector<float>> &vec, //distances
    set<int>& candidateSet, //V
    double alpha,
    size_t R
) {

//adding every neighbor of p in the candidate Set
    map <pair <int,int>,float> distances;
    
    for (int neighbor : graph[point]) 
    {  
        //if(neighbor!=point)
            candidateSet.insert(neighbor); //Inserting all the nighbors of point in the candidate_set
    }
    
    graph[point].clear();
    
    int p; //p will contain the nearest neighbor.Initialized with -1 to ensure it starts as empty 
    euclidean_distance(candidateSet,point,vec,distances);
    cout <<"the candidate set is: ";
    for(int candidate : candidateSet){
        cout << candidate<<" ";
    }    
    cout<<endl;

    while (candidateSet.empty()!=1){
        cout<<"I am inside the while"<<endl;
        p=pickingP(point,candidateSet,distances); //choosing the node from the candidate set with the smallest distance from corrent point and adressing it to p
        cout <<"I am before pushing back and the p is "<< p<<"and the point is "<<point <<endl;
       
        cout << endl;        
        graph[point].push_back(p);  //SEGMENTATION!!!
        cout<< "I am after the pushing_back"<<endl;
        if(graph[point].size()==R ) 
            break;
        
        map<pair <int,int>,float> distancePtoCand;
        euclidean_distance(candidateSet,p,vec,distancePtoCand);
        for (auto candidate = candidateSet.begin(); candidate != candidateSet.end(); ) {

        

            

            if (alpha * distancePtoCand[make_pair(p, *candidate)] <= distances[make_pair(point, *candidate)]) 
                candidate = candidateSet.erase(candidate);  // Erase also updates the  iterator to next element
            else 
                candidate++;  // if not erasion happens, we move the iterator manually to the next element.
        }
    }



}