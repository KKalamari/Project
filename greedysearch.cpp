#include <iostream>
#include <string>
#include <vector>
#include "graph_creation.h"
#include "reading.h"
using namespace std;

//s->starting node, xq->query point, k->result size, search_list_size->L >=k
void greedysearch(vector <int> s,int query_point,int k_neigh,int L_sizelist)
{
    //vector<int>* graph = graph_creation(); 
    vector <int> SetL;
    SetL.push_back(s.at(0)); //initializing set L with s
    vector<int>SetV ; //initializing the set of visited nodes (now it's empty)
    vector <int>unvisited;
    unvisited.push_back(s.at(1)); //adding the neighborhood of the current s node as unvisited
    while(unvisited.empty()==1)
    {
        if(SetL.size()==1){
            int p=SetL.back();
            SetL.pop_back();
        }
        else{      //calculating euclidean distance
            
        }

    }

}

int main(){

}