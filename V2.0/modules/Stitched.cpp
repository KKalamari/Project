#include "Vamana.h"
#include "Stitched.h"
#include <omp.h>
using namespace std;

map<int,set<int>> StitchedVamana(vector <vector<float>>& DataNodes,
set<float> &category_attributes,
double a,int L_small,int R_small, int R_stitched
,vector<vector<double>>& vecmatrix,
map<float,int> M,int thread_num){
    vector <float> categories(category_attributes.begin(),category_attributes.end());
    int different_categories = categories.size();
    map <int,set <int>> Gf;
        //categorizing each node to it's label

    map<float,list<int>> labeled_nodes;
    for(int i=0; i<DataNodes.size();i++){
        labeled_nodes[DataNodes[i][0]].push_back(i); 
    }
    int count = thread_num;
    #pragma omp parallel for num_threads(count) schedule(dynamic)
    for( int i=0;i<different_categories;i++){
        map<int,set<int>>tempGf =vamana_index_algorithm(labeled_nodes,categories[i],a,R_small,L_small,vecmatrix,M,R_stitched,thread_num);
        #pragma omp critical //because of the critical section the increase in performance is minimum
        for(auto CurrList : tempGf ){
            set <int> set_of_nodes_to_insert= CurrList.second;
            for(auto nodes : set_of_nodes_to_insert){
                Gf[CurrList.first].insert(nodes);
            }
        }
    }
    save_graph_to_binary_set(Gf, "graph_data_from_stitched.bin");
    return Gf;




}