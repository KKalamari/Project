
#include"FilteredRobust.h"
#include <chrono>
void pickingp_star(int& p_star,int&p,vector<vector<double>>& vecmatrix,set<int> &V){
    double mindist=DBL_MAX;
    for(auto Vneighbors : V){
        if(mindist>vecmatrix[p][Vneighbors]){
            mindist=vecmatrix[p][Vneighbors];
            p_star=Vneighbors;
        }
    }

}




void FilteredRobustPrune(map <int,list<int>>&graph,int &p,set<int> &V,double &alpha,int&R,vector<vector<double>> &vectormatrix,vector<vector<float>>&dataset){
    auto starting_time =std::chrono::system_clock::now();

    for(auto OutNeighbors : graph[p]){
        V.insert(OutNeighbors);
    }

   
    graph[p].erase(graph[p].begin(),graph[p].end());
    V.erase(p);
    int p_star;    
    while (V.empty()!=1){
        pickingp_star(p_star,p,vectormatrix,V);
        // cout <<"pushing back "<<p_star<<endl;
        graph[p].push_back(p_star);
        if(int(graph[p].size())>=R){
            break;
        }
        set<int> nodes_to_be_deleted;
        for(auto& Vneighbors : V){
            if(dataset[p][0]==dataset[Vneighbors][0] && dataset[p_star][0]!=dataset[Vneighbors][0]){
                // cout<<"I am before continuing "<<endl;
                cout<<"CONTINUING!!!-------------------------------------------------------------------------------------------------------------"<<endl;
                continue;
            }
            
            if(alpha*vectormatrix[p_star][Vneighbors]<=vectormatrix[p][Vneighbors])
                nodes_to_be_deleted.insert(Vneighbors);
        }
        // cout<<"nodes to be deleted size is "<< nodes_to_be_deleted.size()<<endl;
        for(auto& deletion_nodes :nodes_to_be_deleted){
            V.erase(deletion_nodes);
        }
    }

        auto end =std:: chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - starting_time;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
       cout << " elapsed time in Filtered Robust : " << elapsed_seconds.count()<<endl;
    
}