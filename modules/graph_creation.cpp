#include "graph_creation.h"
using namespace std;



map <int, list<int>> graph_creation(vector<vector<float>>&vec, int R ){
    cout<< "the vector size is: "<< vec.size() <<"\n";
    map <int, list<int>> adj;
    
    srand(time(0)); 

    
    for(int i=0;i<int(vec.size());i++){
        for (int j=0;j<R;j++){
            int random_number = rand() % (vec.size());//generating numbers from 0 to vec->size 
            if (find(adj[i].begin(), adj[i].end(), random_number) == adj[i].end() && i!=random_number)  //not found nor i=R thus adding neighbor
                adj[i].push_back(random_number);
            else{
                j--;
                // cout<<"hello never ending torment"<<endl;
                continue; //redo the loop until you find some neighbor which is not already in the list or not its self.
            }
        
    }
    }

    return adj;
}

