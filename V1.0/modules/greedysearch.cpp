
#include "greedysearch.h"
using namespace std;

//function that ensures that L contains at leasτ one node which haven't been already explored.
bool unexplored_nodes(list <int>L,list <int>visited){ 
    
    for(list <int> :: iterator lit=L.begin();lit!=L.end();lit++){//for every element there is in L
        bool found=0;
        list <int> :: iterator vit=visited.begin(); //we iterate V list
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

//The same logic with the above just for a specific node
bool unexplored_node(int node, const list<int> visited) { 
    for (auto vit = visited.begin(); vit != visited.end(); vit++) {
        if (*vit == node) {
            return 0;//just found a match in visites list 
        }
    }
    return 1; //node does not exist in the visited list
}

void addtoL(list<int> neighbors, list<int> &L, vector<vector<double>> &querymatrix, int Lsizelist, int &query)
{
}


//adding the neighbors of the node which P contains in a sorted way.Also prunes the nodes when overextending the L_sizelist.
void addtoL(list <int> neighbors,list <int> &L,vector<vector<double>>&querymatrix,int Lsizelist,int& query){
    list <int>:: iterator nit;
    list <int>:: iterator lit;
    for(nit=neighbors.begin();nit!=neighbors.end();nit++){

        bool inserted=0; //POSSIBLE OVERTHINKING!!!
        if(unexplored_node(*nit,L)){ // if the node does not already exist in L
            for(lit=L.begin();lit!=L.end();lit++){
                if(querymatrix[*nit][query]<querymatrix[*lit][query]){
                    L.insert(lit,*nit);
                    if(int(L.size())>Lsizelist){
                        L.pop_back(); //erasing the last element,the one with the greater value,from set L
                    }
                    inserted=1;
                    break;
                }
            }

        }
        if(inserted==0){
            if(int(L.size())<Lsizelist){
                L.push_back(*nit);
            }
            
            //else do nothing. If L.size()>Lsizelist and the new element is the bigger one, it will be added and be removed instantly
            //so we're doing nothing!
            
        }
    
    }
}


//firtsly accepts the random R-graph finally the vamana index graph,s=starting node,query_point is the node we want to find the nearest neighbors
//querymatrix is a matrix of distances between every vec node we have read and the query points we also read.
pair <set <int>,set <int>> greedysearch( map <int, list<int>>& graph,int &s,int& query_point,int &k_neigh,int &L_sizelist,vector<vector<double>>&querymatrix){
    list <int> L; //list L will contain the neighbors of each node we have traversed. It's initialized with S as the starting_node    
    list<int> V; //list containing all the visited nodes we already traversed and searched their nεighbours
    addtoL(graph[s],L,querymatrix,L_sizelist,query_point); //passing the neighbors of s which will be added to L
   
    V.push_back(s); //it->first s traversed, we put it in the visited list

    int p; //this will hold the nearest neighbor from the query which exists in L
    list <int>::iterator Literator=L.begin();
    while( unexplored_nodes(L,V)==1){  //while there are still unexplored nodes in L
        Literator = L.begin();
        p=*Literator; 
        while(unexplored_node ( p,V )==0){ //ensuring p does not show in a node we have already traversed.
            Literator++;
            p=*Literator;
            if (Literator != L.end()) {
                p = *Literator;
            } else {
                break; 
            }
        }
   
        addtoL(graph[p],L,querymatrix,L_sizelist,query_point); //adding to L the neighbors of the current node we are in.
       
        V.push_back(p); //pushing back to V the traversed node.
    
        
    }

    while(int(L.size())>k_neigh)
        L.pop_back();
    
    
    set <int> Lset;
    set <int> Vset;

    for (list <int> :: iterator vit=V.begin();vit!=V.end();vit++){
        Vset.insert(*vit);
    } 

    for(list <int> ::iterator lit=L.begin();lit!=L.end();lit++){
        Lset.insert(*lit);
    }

    
    return make_pair(Lset,Vset); //returning L which contains the k nearest neighbors
}

