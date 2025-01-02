#include "Vamana.h"
#include "Stitched.h"
using namespace std;

map<int,set<int>> StitchedVamana(vector <vector<float>>& DataNodes,
set<float> &category_attributes,
double a,int L_small,int R_small, int R_stitched
,vector<double>& vecmatrix,
map<float,int> M){
    map <int,set <int>> Gf;
        //categorizing each node to it's label

    map<float,list<int>> labeled_nodes;
    for(int i=0; i<DataNodes.size();i++){
        labeled_nodes[DataNodes[i][0]].push_back(i); 
    }


    for( auto filters: category_attributes){

        map<int,set<int>>tempGf =vamana_index_algorithm(labeled_nodes,filters,a,R_small,L_small,vecmatrix,M,R_stitched);
        for(auto CurrList : tempGf ){
            set <int> set_of_nodes_to_insert= CurrList.second;
            for(auto nodes : set_of_nodes_to_insert){
                Gf[CurrList.first].insert(nodes);
            }
        }
    }
//save_graph_to_binary_set(Gf, "graph_data_from_stitched.bin");
    return Gf;




}