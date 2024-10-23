#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include "graph_creation.h"
#include "euclidean_distance.h"
#include <reading.h>
#include <list>
#include <map>
#include <utility>



using namespace std;


//POSSIBLE MISTAKE!!!!
bool unexplored_nodes(list <int>L,list <int>visited){ 
    
    for(list <int> :: iterator lit=L.begin();lit!=L.end();lit++){ //for every element available in L
        bool found=0;
        list <int> :: iterator vit=visited.begin(); //iterator for V list
        for(vit=visited.begin();vit!=visited.end();vit++){
        if(*vit==*lit){
            found=1;
            break;
        }
    }
    if(found==0)
        return 1; //just found an unexplored node, return 1
    }
    return 0; //every node has been explored

}

//aading the neighbors of the node which P contains in a sorted way.Also prunes the nodes which overextend the L_sizelist.
void addtoL(list <int> neighbors,list <int> &L,map <int,float>distances,int Lsizelist){
    list <int>:: iterator nit;
    list <int>:: iterator lit;
    cout << " I am inside the addtoL"<<endl;
    for(nit=neighbors.begin();nit!=neighbors.end();nit++){
        bool inserted=0; //POSSIBLE OVERTHINKING!!!
        if(find(L.begin(), L.end(), *nit) == L.end()){ // if the node does not already exist in L
            for(lit=L.begin();lit!=L.end();lit++){
                if(distances[*nit]<distances[*lit]){
                    L.insert(lit,*nit);
                    if(int(L.size())>Lsizelist){
                        L.erase(--L.end()); //erasing the last element,the one with the greater value,from set L
                    }
                    inserted=1;
                    break;
                }
            }
        }
        if(inserted==0){
            if(int(L.size())<Lsizelist)
                L.push_back(*nit);
            //else do nothing. If L.size()>Lsizelist and the new element is the bigger one, it will be added and be removed instantly
            //so we're doing nothing!
            
        }
    }
}


//s->starting node, xq->query point, k->result size, search_list_size->L >=k
pair <set <int>,set <int>> greedysearch( map <int, list<int>>& s,vector<float> query_point,int k_neigh,int L_sizelist,map <int,float>distances){
    //initialize set L
    map <int, list<int>>::iterator it; //https://www.geeksforgeeks.org/iterators-c-stl/
    it=s.begin();
    list <int> L; //List L will contain the neighbors of each node we have traversed. It's initialized with S as the starting_node
    cout<< " I am before addtoL()"<<endl;
    addtoL(it->second,L,distances,L_sizelist); //passing the neighbors of s which will be added to L
    list<int> V; //list containing all the visited nodes we already traversed and searched their naighbours
    cout << "I am before inserting a visited node"<<endl;
    V.push_back(it->first); //s traversed, we put it in the visited list
    int p; //this will hold the nearest neighbor the query
    cout << " I am before the while"<<endl;
    while(L.empty()!=0 && unexplored_nodes(L,V)==1){ 
        p=int(*next(L.begin(), 0)); // p=first node of set L
        L.erase( next(L.begin(), 0)); 
        cout <<"I am in the while"<<endl;
        addtoL(s[p],L,distances,L_sizelist);
        V.push_back(p);
        
        
    }
  
    while(int(L.size())>k_neigh){
        L.pop_back();
    }

    set <int> Lset;
    set <int> Vset;
    for(list <int> ::iterator lit=L.begin();lit!=L.end();lit++){
        Lset.insert(*lit);
    }

    for (list <int> :: iterator vit=V.begin();vit!=V.end();vit++){
        Vset.insert(*vit);
    } 
    return make_pair(Lset,Vset); //returning L which contains the k nearest neighbors
}

