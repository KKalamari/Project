#include "FilteredRobust.h"
#include "FilteredGreedySearch.h"
#include "euclidean_distance.h"
#include"acutest.h"

/*
building the instance(Initializing dataset,p and graph. The filtered robust should keep the least distanced nodes and keep
the nearest ones which it's actually happening in our example.)
*/




void FilteredRobustTest(){
    vector<vector<float>>dataset={{6,5,1,4},{1,5,5,3},{1,5,3,4},{6,5,6,1},{6,3,4,2},{6,1,2,2}};
    map<int,set<int>> graph;
    int p=3;
    double alpha=1;
    int R=1;

    vector<vector<double>> vectormatrix(dataset.size(),vector<double>(dataset.size())); //6 x 6 matrix
    euclidean_distance_of_database(dataset,vectormatrix);
  
    set<int>V1({5, 0, 3});
    graph[0]={1,3,5};
    graph[1]={0,3,5};
    graph[3]={4,0,5};
    graph[2]={4};
    graph[4]={2};
    graph[5]={1,3,0};

    FilteredRobustPrune(graph,p,V1,alpha,R,vectormatrix,dataset);
    //testing for alpha=1 R=1
    if(TEST_CHECK(find(graph[p].begin(), graph[p].end(), 4) != graph[p].end()))//5 is the nearest neighbor.
        cout<<"test for alpha=1 succeded!"<<endl;
    //testing for alpha=1 R=2. The result should be the same as before because even though the threshold increased the alpha remained the same.
    R=2;
    set<int>V2({5, 0, 3});

    FilteredRobustPrune(graph,p,V2,alpha,R,vectormatrix,dataset);
    if(TEST_CHECK(find(graph[p].begin(), graph[p].end(), 4) != graph[p].end()))
        cout <<"test for alpha=1,R=2 succeded!"<<endl;


    alpha=6; R=2;
    set<int>V3({5, 0, 3});

    FilteredRobustPrune(graph,p,V3,alpha,R,vectormatrix,dataset);

    //testing for alpha=3 R=2. Now the neighbors of p should be 2 nodes instead of just 1. First the node 5 as the nearest one, then node 0.
    set<int>::iterator Vit=graph[p].begin();
    TEST_CHECK(*Vit==4);
    Vit++;
    if(TEST_CHECK(*Vit==5))
        cout<<"testing for bigger alpha and R=2 succeded!"<<endl;


}


TEST_LIST{
    {"FilteredRobustTest",FilteredRobustTest},
    {"NULL",NULL}
};



// the euclidean distance for node 0 is: 0
// the euclidean distance for node 0 is: 4.12311
// the euclidean distance for node 0 is: 2
// the euclidean distance for node 0 is: 5.83095 THIS ONE
// the euclidean distance for node 0 is: 3.60555
// the euclidean distance for node 0 is: 2.23607
// the euclidean distance for node 1 is: 4.12311
// the euclidean distance for node 1 is: 0
// the euclidean distance for node 1 is: 2.23607
// the euclidean distance for node 1 is: 2.23607 //THIS ONE
// the euclidean distance for node 1 is: 1.41421
// the euclidean distance for node 1 is: 3.16228
// the euclidean distance for node 2 is: 2
// the euclidean distance for node 2 is: 2.23607
// the euclidean distance for node 2 is: 0
// the euclidean distance for node 2 is: 4.24264
// the euclidean distance for node 2 is: 2.23607
// the euclidean distance for node 2 is: 2.23607
// the euclidean distance for node 3 is: 5.83095
// the euclidean distance for node 3 is: 2.23607
// the euclidean distance for node 3 is: 4.24264
// the euclidean distance for node 3 is: 0
// the euclidean distance for node 3 is: 2.23607
// the euclidean distance for node 3 is: 4.12311
// the euclidean distance for node 4 is: 3.60555
// the euclidean distance for node 4 is: 1.41421
// the euclidean distance for node 4 is: 2.23607
// the euclidean distance for node 4 is: 2.23607 //THIS ONE
// the euclidean distance for node 4 is: 0
// the euclidean distance for node 4 is: 2
// the euclidean distance for node 5 is: 2.23607
// the euclidean distance for node 5 is: 3.16228
// the euclidean distance for node 5 is: 2.23607
// the euclidean distance for node 5 is: 4.12311 //THIS ONE
// the euclidean distance for node 5 is: 2
// the euclidean distance for node 5 is: 0