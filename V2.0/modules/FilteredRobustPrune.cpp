
#include"FilteredRobust.h"
#include <chrono>
#include <limits>
#include "Euclidean_distance.h"


//finding the mindist to  a node which exists in V from the p element
void pickingp_star(int& p_star,int&p,vector<double>& vecmatrix,set<int> &V){
    double mindist=numeric_limits<double>::max();
    int n = vecmatrix.size();
    for(auto Vneighbors : V){
        if(mindist> vecmatrix[matrix_to_triangular(p,Vneighbors,n)]) {
            mindist= vecmatrix[matrix_to_triangular(p,Vneighbors,n)];
            p_star=Vneighbors;
        }
    }

}




int FilteredRobustPrune(map <int,set<int>>&graph,
int &p,
set<int> &V,
double &alpha,
int&R,
vector<double>&vectormatrix,
vector<vector<float>>&dataset){
    int n = vectormatrix.size();
    auto starting_time =std::chrono::system_clock::now();

    for(auto OutNeighbors : graph[p]){
        if(OutNeighbors!=p)
            V.insert(OutNeighbors);
    }

   
    graph[p].clear();
    V.erase(p);
    int p_star;    
    int counter=0;
    while (V.empty()!=1){
        pickingp_star(p_star,p,vectormatrix,V);
        graph[p].insert(p_star);
        
        if(int(graph[p].size())>=R)
            break;
        
        set<int> nodes_to_be_deleted;
        for(auto Vneighbors : V){
            if(dataset[p][0]==dataset[Vneighbors][0] && dataset[p_star][0]!=dataset[Vneighbors][0]){
                // cout<<"I am before continuing "<<endl;
                //It's actually never printed
                cout<<"CONTINUING!!!-------------------------------------------------------------------------------------------------------------"<<endl;
                continue;
            }
            
            if(alpha*vectormatrix[matrix_to_triangular(p_star,Vneighbors,n)] <=vectormatrix[matrix_to_triangular(p,Vneighbors,n)] ){
                counter++;
                nodes_to_be_deleted.insert(Vneighbors);
            }
        }
        for(auto& deletion_nodes :nodes_to_be_deleted){
            V.erase(deletion_nodes);
        }
    }

        auto end =std:: chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - starting_time;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    //    cout << " elapsed time in Filtered Robust : " << elapsed_seconds.count()<<endl;
    return counter;
}