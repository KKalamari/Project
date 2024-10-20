#include <iostream>
#include <string>
#include <vector>
#include "euclidean_distance.h"
#include <list>
#include <algorithm>
#include <map>
#include <set>
using namespace std;



map <int, set<int>> graph_creation(vector<vector<float>>*vec,int k, int R ){
    cout<< "the vector size is: "<< vec->size() <<"\n";
    cout << "the k is: "<< k <<endl;
    map <int, set<int>> adj;
    
    srand(time(0)); 

    
    for(int i=0;i<int(vec->size());i++){
        for (int j=0;j<R;j++){
            int random_number = rand() % (vec->size()); //generating numbers from 0 to vec->size 
            if (find(adj[i].begin(), adj[i].end(), random_number) == adj[i].end() && i!=random_number)  //not found nor i=R thus adding neighbor
                adj[i].insert(random_number);
            else{
                j--;
                cout<<"hello never ending torment"<<endl;
                continue; //redo the loop until you find some neighbor which is not already in the list or not its self.
            }
        
    }
    }

    // cout << "Graph adjacency list:\n";
    // for (const auto& node : adj) {
    //     cout << "Node " << node.first << ": ";
    //     for (const auto& neighbor : node.second) {
    //         cout << neighbor << " ";
    //     }
    //     cout << endl;
    // }
    return adj;
}

