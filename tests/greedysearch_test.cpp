#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include "acutest.h" 
#include "greedysearch.h"
#include "euclidean_distance.h"
#include "reading.h"
using namespace std;


void test_greedyseach(){

    vector <vector<float>> vec {
        {10.0,5.0,27.0,35.0,12.0,144.0,15.75,88.25,56.0,23.5}, //3rd 170.012
        {0.0,2.5,192.0,47.3,65.8,32.0,276.0,8.0,19.37,4.0}, //307.668
        {13.0,21.0,42.0,3.0,75.0,98.0,24.0,29.0,8.0,11.0}, //161.637 2nd smaller
        {26.0,1.0,22.0,10.0,2.0,97.0,76.0,34.0,32.0,55.0}, //3rd smaller 162.591
        {11.0,22.0,52.0,68.0,69.0,112.0,25.0,444.0,777.0,8.0} //839.809

    };

    map <int,list<int>>graph;
    vector <vector<float>> xq={{13.0,78.6,45.7,77.0,12.3,3.0,39.7,90.0,27.8,12.8}};
    int k_neigh=3;
    int L_sizelist=4;

    graph[0] = {1,3,4};
    graph[1] = {0,1,2};
    graph[2] = {2,3,4};
    graph[3] = {0,3,4};
    graph[4] = {1,2,3};
    cout <<"xqsize is "<<xq.size()<<endl;
    vector<vector<double>> queries(vec.size(),vector<double>(xq.size()));
    euclidean_distance_of_queries(vec,xq,queries);
    int s=3;
    map <int,double>distances;
    pair <set <int>,set<int>> pairSet;
    int q=0;
    pairSet = greedysearch( vec,graph,s,q, k_neigh, L_sizelist,queries);
    set <int> L=pairSet.first;
    TEST_CHECK(int(L.size())==k_neigh);
    cout << "the L set is:";
    for(auto nodes : L){
        cout << nodes <<" ";
    }
    cout <<endl;
    TEST_CHECK(L.find(0)!=L.end());
    TEST_CHECK(L.find(2)!=L.end());
    TEST_CHECK(L.find(3)!=L.end());
}

TEST_LIST{
    {"test_greedysearch",test_greedyseach},
    {NULL,NULL}

};