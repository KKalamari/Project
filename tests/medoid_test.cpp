#include "acutest.h"
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <iostream>
#include <set>
#include "vamana.h"



void testing_modoiod(){
    vector<vector<float>>vec={
        {1,2,3,4},
        {4,5,6,7},
        {1,1,1,1},
        {2,3,5,7},
        {8,6,7,5},
        {3,3,3,3},
        {6,6,6,6},
        {5,8,5,3}
};

int medoid_node= medoid(vec);
cout <<"medoid_node is: " <<medoid_node<<endl;
TEST_CHECK(medoid_node==5);
}

// void vamana_testing(){
    

//     vector<vector<float>>vec={
//         {1,2,3,4},
//         {4,5,6,7},
//         {1,1,1,1},
//         {2,3,5,7},
//         {8,6,7,5},
//         {3,3,3,3},
//         {6,6,6,6},
//         {5,8,5,3}
// };
    
//     int medoid_test;
//     int R=2;
//     int L;
//     int a;
//     vector<vector<double>>vecmatrix(vec.size(),vector<double>(vec.size()));
//    map<int,list<int>> graph= vamana_index_algorithm(vec,R,medoid_test,L,a,vecmatrix);
//     for(int i=0;i<int(graph.size());i++){
//         cout <<" node i "<<i <<" has neighbors ";
//         for(auto nodes : graph[i]){
//             cout <<nodes << " ";
//         }
//         cout<<endl;
//     }
//     }


TEST_LIST{
    "testing_medoid",testing_modoiod,
    // "vamana_testing",vamana_testing,
    {NULL,NULL}
};
