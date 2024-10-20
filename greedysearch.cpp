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
        return 1;
    }
    return 0; //every node has been explored

}

//CORRECT
void addtoL(list <int> neighbors,list <int> &L,map <int,float>distances,int Lsizelist){
    list <int>:: iterator nit;
    list <int>:: iterator lit;
    for(nit=neighbors.begin();nit!=neighbors.end();nit++){
        bool inserted=0; //POSSIBLE OVERTHINKING!!!
        if(find(L.begin(), L.end(), *nit) == L.end()){ // if the node does not already exist in L
            for(lit=L.begin();lit!=L.end();lit++){
                if(distances[*nit]<(distances[*lit])){
                    L.insert(lit,*nit);
                    if(int(L.size())>Lsizelist)
                        L.pop_back();
                    inserted=1;
                    break;
                }
            }
        }
        if(inserted==0){
            L.push_back(*nit);
            if(int(L.size())>Lsizelist)
                L.pop_back();
        }
    }
}


            
// float minimum_distance(list <int> L,map <int,float>& distances,int &p){
//     list <int>::iterator lit;
//     float mindist=distances[L.front()]-1; //making sure it's less than the actual distance of the first node
//     for(lit=L.begin();lit!=L.end();lit++){
//         if(mindist>distances[*lit]){
//             mindist=distances[*lit];
//             p=int(*lit);
//         }

//     }
//     return mindist;
// }


// void pruning_nodes(int nodes_to_detele,map <int,float>distances,list <int>& L){
//     float maxdist=L.front()-1;
//         list <int>:: iterator lit;
//         for(nodes_to_detele;nodes_to_detele!=0;nodes_to_detele--){
//             L.pop_back(); //removing the last element of the list, thus the one with the bigger distance.
//     }
// }



//s->starting node, xq->query point, k->result size, search_list_size->L >=k
list <int> greedysearch( map <int, list<int>> s,vector<float> query_point,int k_neigh,int L_sizelist,map <int,float>distances){
    //initialize set L
    map <int, list<int>>::iterator it; //https://www.geeksforgeeks.org/iterators-c-stl/
    it=s.begin();
    list <int> L; //List L will contain the neighbors of each node we have traversed. It's initialized with S as the starting_node
    addtoL(it->second,L,distances,L_sizelist); //passing the neighbors of s which will be added to L
    list<int> V; //list containing all the visited nodes we already traversed and searched their naighbours
    V.push_back(it->first); //s traversed, we put it in the visited list
    int p; //this will hold the nearest neighbor the query

    while(L.empty()!=0 && unexplored_nodes(L,V)==1){
        p=L.front();
        L.pop_front();
        addtoL(s[p],L,distances,L_sizelist);
        V.push_back(p);
        
        
    }
    if(int(L.size())>k_neigh){
        for(int i=L.size();i>k_neigh;i++)
        L.pop_back(); //removing the last elemt of the list, thus the bigger one.
    }

    return L; //returning L which contains the k nearest neighbors
}

