#include "FilteredVamana.h"
#include "euclidean_distance.h"
#include "medoid.h"
#include "Stitched.h"
#include "acutest.h"

/* 
In the 3nd assignemnt Vanana dot not result in a well connected graph. Thu's we're  going to 
have 2 diffrent graphs, 1 with filter = 6 and another with filter = 1.

The important thing is that every node has a neighbor of the same filter category!
*/

void FilteredVamana(){
    vector<vector<float>>DataNodes={{6,5,1,4},{1,5,5,3},{6,5,3,4},{6,5,6,1},{1,3,4,2},{6,1,2,2}};
    vector<vector<double>> vectormatrix(DataNodes.size(),vector<double>(DataNodes.size()));
    double alpha=1.0;
    int R=13; //too big for our example, that's ok though.
    map<float,int>M;
    set<float> category_attributes;
    category_attributes.insert(1.0);
    category_attributes.insert(6.0);
    M = FindMedoid(DataNodes,1,category_attributes);
    map<int,set<int>> graph = FilteredVamanaIndex(vectormatrix,DataNodes,alpha,R,category_attributes,M);
    int Vamana_size = graph.size();
    cout<<"the graph size is "<< Vamana_size<<endl;
    for(int i=0;i<Vamana_size;i++){
        cout <<i<<" node has neighbors: ";
        for(auto neighbors : graph[i]){
            cout <<neighbors << " ";
            TEST_CHECK(DataNodes[i][0]==DataNodes[neighbors][0]);
        }
        cout<<endl;
    }

}




void StitchedVamana_test(){

    vector<vector<float>>DataNodes={{6,5,1,4},{1,5,5,3},{6,5,3,4},{6,5,6,1},{1,3,4,2},{6,1,2,2}};
    vector<vector<double>> vectormatrix(DataNodes.size(),vector<double>(DataNodes.size()));
    double alpha=1.0;
    int R=13; //too big for our example, that's ok though.
    map<float,int>M;
    int L_small=100;
    set<float> category_attributes;
    category_attributes.insert(1.0);
    category_attributes.insert(6.0);
    M = FindMedoid(DataNodes,1,category_attributes);
    map<int,set<int>> graph = StitchedVamana(DataNodes,category_attributes,alpha,L_small,R,R,vectormatrix,M,L_small);
    int Vamana_size = graph.size();
    cout<<"the graph size is "<< Vamana_size<<endl;
    TEST_CHECK(graph.size()==6); //checking if every node has been assigned a naighbor


    //checking if the R limit is enforced
    graph = StitchedVamana(DataNodes,category_attributes,alpha,L_small,1,1,vectormatrix,M,L_small); 
    for(int i=0;i<Vamana_size;i++){
        cout <<i<<" node has neighbors: ";
        for(auto neighbors : graph[i]){
            cout <<neighbors << " ";
        }
        TEST_CHECK(graph[i].size()==1);
        cout<<endl;
    }
}











TEST_LIST{
    {"FilteredVamanaTest",FilteredVamana},
    {"StitchedVamana_test",StitchedVamana_test},
    {"NULL",NULL}
};