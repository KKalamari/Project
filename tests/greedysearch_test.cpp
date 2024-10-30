#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include "acutest.h"  // Include Acutest
#include "greedysearch.h"

using namespace std;

// checking if the searching for an unexplored node in L happens correctly.
void test_unexplored_nodes(){
    list <int> L ={0,1,2};
    list <int> V ={1,2,3};
    bool biased_checker=1; //L contains zero which does not exist in V
    bool actual_checker=unexplored_nodes(L,V);
    TEST_CHECK(actual_checker==biased_checker);

    L={0,1,2,3}; //L contains "1 " which does not exist in V
    V={0,2,3};
    actual_checker= unexplored_nodes(L,V);
    TEST_CHECK(actual_checker==biased_checker);

    L={0,1,2}; //contains the "2" which does not exist in V
    V={0,1,3,4};
    actual_checker= unexplored_nodes(L,V);
    TEST_CHECK(actual_checker==biased_checker);

    //unexplored nodes return 0 because L has the same nodes as V

    L={0,1,2,3};
    V={0,1,2,3};
    biased_checker=0;
    actual_checker=unexplored_nodes(L,V);
    TEST_CHECK(actual_checker==biased_checker);

    L={0,1,2};
    V={0,1,2,3};
    actual_checker=unexplored_nodes(L,V);
    TEST_CHECK(actual_checker==biased_checker);

}

//checking if the addition of neighbor nodes in L list happends correctly.
void test_addtoL(){
    list <int> L;
    list <int> neighbors;
    map <int,double> distances;
    int L_sizelist;

    L_sizelist=3;
    neighbors={1,2,3};
    distances={{1,float(7.65)},{2,float(4.5)},{3,float(8)}};
    addtoL(neighbors,L,distances,L_sizelist);

    list <int>::iterator lit=L.begin();
    TEST_CHECK(*lit==2);
        lit++;
        TEST_CHECK(*lit==1);
        lit++;
        TEST_CHECK(*lit==3);
    }


    //checking the greedysearch basic functions
void greedy_search(){
    //checking if the p function the way it should.
    map <int, list<int>> graph;
    graph[0]={1,2};
    graph[1]={3,0};
    graph[2]={1,3};
    graph[3]={2,0};
    int s=0;
    
    map <int,double>distances; //distance of the <int> node from the query 
    distances[0] = 8.0;
    distances[1]=2.5;
    distances[2]=2.5;
    distances[3]=2.0;
    vector<float> xq={1.5};
    pair <set <int>,set <int>> PairSet;
    PairSet = greedysearch(graph,s,xq,2,4,distances);


    }


TEST_LIST{
    {"test_unexplored_nodes",test_unexplored_nodes},
    {"test_addtoL()",test_addtoL},
    {"greedy_search",greedy_search},
    {NULL, NULL}  // Terminate the test list


};