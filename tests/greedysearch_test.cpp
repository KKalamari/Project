#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include "acutest.h"  // Include Acutest
#include "greedysearch.h"
#include "euclidean_distance.h"
#include "reading.h"
using namespace std;

//checking if the searching for an unexplored node in L happens correctly.
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
    const char* filename="siftsmall_base.fvecs";
    const char* filename2 = "siftsmall_query.fvecs";
   vector <vector<float>> vec=reading_fvecs(filename,1,10000); //διαβάζει τα 10000 vectors/nodes μαζί με τις συντεταγμένες του καθενός
   vector <vector <float>> query_vec= reading_fvecs(filename2,1,100); //διαβάζει τις συντεταγμένες του καθε query.
    PairSet = greedysearch(vec,graph,s,query_vec,2,4,distances);
    set <int> L= PairSet.first;
    for


    }


TEST_LIST{
    {"test_unexplored_nodes",test_unexplored_nodes},
    {"test_addtoL()",test_addtoL},
    {"greedy_search",greedy_search},
    {NULL, NULL}  // Terminate the test list


};


// void test_greedyseach(){

//     vector <vector<float>> vec {
//         {10.0,5.0,27.0,35.0,12.0,144.0,15.75,88.25,56.0,23.5}, //smallest
//         {0.0,2.5,192.0,47.3,65.8,32.0,276.0,8.0,19.37,4.0},
//         {13.0,21.0,42.0,3.0,75.0,98.0,24.0,29.0,8.0,11.0}, //161.637 2nd smaller
//         {26.0,1.0,22.0,10.0,2.0,97.0,76.0,34.0,32.0,55.0}, //3rd smaller
//         {11.0,22.0,52.0,68.0,69.0,112.0,25.0,444.0,777.0,8.0} //839.809

//     };

//     map <int,list<int>>graph;
//     vector<float> xq={13.0,78.6,45.7,77.0,12.3,3.0,39.7,90.0,27.8,12.8};
//     int k_neigh=3;
//     int L_sizelist=4;

//     graph[0] = {1,3,4};
//     graph[1] = {0,1,2};
//     graph[2] = {2,3,4};
//     graph[3] = {0,3,4};
//     graph[4] = {1,2,3};

//     int s=3;
//     map <int,double>distances;
//     pair <set <int>,set<int>> pairSet;
//     pairSet = greedysearch( vec,graph,s,xq, k_neigh, L_sizelist,distances);
//     set <int> L=pairSet.first;
//     TEST_CHECK(int(L.size())==k_neigh);
//     cout << "the L set is:";
//     for(auto nodes : L){
//         cout << nodes <<" ";
//     }
//     cout <<endl;
//     TEST_CHECK(L.find(0)!=L.end());
//     TEST_CHECK(L.find(2)!=L.end());
//     TEST_CHECK(L.find(3)!=L.end());
// }

// TEST_LIST{
//     {"test_greedysearch",test_greedyseach},
//     {NULL,NULL}

// };