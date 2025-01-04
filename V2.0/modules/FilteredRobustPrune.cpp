
#include"FilteredRobust.h"
#include <chrono>
#include <limits>

//finding the mindist to  a node which exists in V from the p element
// void pickingp_star(int& p_star,int&p,vector<vector<double>>& vecmatrix,set<int> &V){
//     double mindist=numeric_limits<double>::max();
//     for(auto Vneighbors : V){
//         if(mindist>vecmatrix[p][Vneighbors]){
//             mindist=vecmatrix[p][Vneighbors];
//             p_star=Vneighbors;
//         }
//     }

// }




int FilteredRobustPrune(map <int,set<int>>&graph,
int &p,
set<int> &V,
double &alpha,
int&R,
vector<vector<double>>&vectormatrix,
vector<vector<float>>&dataset){
    auto starting_time =std::chrono::system_clock::now();
    pair<double,int> node;
    set<pair<double,int>> ordered_V;
    for(auto Vneighbors : V){
        node = make_pair(vectormatrix[p][Vneighbors],Vneighbors);
        ordered_V.insert(node);
    }

    for(auto OutNeighbors : graph[p]){
        if(OutNeighbors!=p)
        node = make_pair(vectormatrix[p][OutNeighbors],OutNeighbors);
            ordered_V.insert(node);
    }

   
    graph[p].clear();
    ordered_V.erase({0.0,p}); //erase the p node which will have distance 0
    int p_star;    
    int counter=0;
    while (ordered_V.empty()!=1){
        set<pair<double,int>>::iterator Vit=ordered_V.begin(); //the first element will always be the one with the minimum distance
        p_star = Vit->second;
        graph[p].insert(p_star);
        
        if(int(graph[p].size())>=R)
            break;
        
        set<int> nodes_to_be_deleted;
        for(auto& Vneighbors_pair : ordered_V){
           int Vneighbors=Vneighbors_pair.second;
            if(dataset[p][0]==dataset[Vneighbors][0] && dataset[p_star][0]!=dataset[Vneighbors][0]){
                // cout<<"I am before continuing "<<endl;
                cout<<"CONTINUING!!!-------------------------------------------------------------------------------------------------------------"<<endl;
                continue;
            }
            
            if(alpha*vectormatrix[p_star][Vneighbors]<=vectormatrix[p][Vneighbors]){
                counter++;
                nodes_to_be_deleted.insert(Vneighbors);
            }
        }
        for(auto& deletion_nodes :nodes_to_be_deleted){
            ordered_V.erase(make_pair(vectormatrix[p][deletion_nodes], deletion_nodes));
        }
    }

        auto end =std:: chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - starting_time;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    //    cout << " elapsed time in Filtered Robust : " << elapsed_seconds.count()<<endl;
    return counter;
}