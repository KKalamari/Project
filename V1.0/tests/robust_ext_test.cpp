#include "robust_ext.h"
#include <iostream>
#include <map>
#include <set>
#include "acutest.h"
#include <utility>
#include <list>
#include "robust_ext.h"
#include "euclidean_distance.h"
using namespace std;

///checking euclidean_distance and pickingP function
void pickingP_test(){ 
    
    vector<vector<float>>vec;       //calculated from https://www.wolframalpha.com/widgets/view.jsp?id=bf56e5c5eba0a8a7a5a6bb9ab5c0169b
    vec.push_back({25.87, 47.64}); //45.3964
    vec.push_back({44.73, 12.11}); //5.17942
    vec.push_back({30.4, 56.96}); //52.1302
    vec.push_back({60.33, 20.55}); //18.2151
    
    set<int> candidate_set;

    // Iterate through vec using an index-based loop
    for (int i = 0; i < int(vec.size()); ++i) {
        candidate_set.insert(i);  // Add the index to the candidate_set
    }
    int point=4; //current p
    cout << " I am before vec"<<endl;
    vec.push_back({47.43,7.69});

    vector <vector<double>> vecmatrix(vec.size(),vector<double>(vec.size()));
    cout << "I am before calling euclidean distance"<<endl;
    euclidean_distance_of_database(vec,vecmatrix);
    //we see it prints indeed the right value for each node
    for(int i=0;i<=3;i++){
        cout << "the  euclidean distance from to cerrunt node of V is : "<< vecmatrix[i][4]<<endl;
    }
    int p;
    
    p= pickingP( point, candidate_set,vecmatrix);
    TEST_CHECK(p==1);
    
}

//checking if the pruning happens correctly.
void robust_prune_test(){

    vector<vector<float>>vec;       //calculated from https://www.wolframalpha.com/widgets/view.jsp?id=bf56e5c5eba0a8a7a5a6bb9ab5c0169b
    vec.push_back({25.87, 47.64}); //45.3964
    vec.push_back({44.73, 12.11}); //5.17942
    vec.push_back({30.4, 56.96}); //52.1302
    vec.push_back({60.33, 20.55}); //18.2151
    vec.push_back({47.43,7.69});
    
    set<int> candidate_set;

    
    int point=4; //current p
    cout << " I am before vec"<<endl;
    

    map<int,list<int>> graph;
    cout <<" I am behind map initialization"<< endl;
    graph[0]={1,2,3};
    graph[1]={2,3,0};
    graph[2]={3,0,1};
    graph[3]={1,2,0};
    graph[4]={0,1,2};
    vector<vector<double>> vecmatrix(vec.size(),vector<double>(vec.size()));
    euclidean_distance_of_database(vec,vecmatrix);

    size_t R=2;
    double alpha=1;
    cout <<"I am behind RobustPrune"<<endl;
    RobustPrune(graph,point,candidate_set,alpha,R,vecmatrix);
    list <int> checking ={1}; //In this example the pruned neighbors are actually <R. 
    cout <<"the graph[4] is: ";
    for(int pruned_neighbors : graph[4]){
        cout << pruned_neighbors;
    }
    cout <<endl;
    TEST_CHECK(graph[4]==checking);

}


TEST_LIST{
    {"pickingP_test",pickingP_test},
    {"robust_prune_test",robust_prune_test},
    {NULL, NULL}  

};

