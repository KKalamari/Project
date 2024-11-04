// greedy.cpp
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "acutest.h"  
#include "graph_creation.h" 

using namespace std;

void test_graph_creation(void) {
    vector<vector<float>> vec;
    vec={{4.5,6.3},{6.2,8.9},{2.0,3.6},{5.4,12.4}};
    int R=3;
        map <int, list<int>> graph =graph_creation(vec,R);
        TEST_CHECK(graph.size()==4);//making sure it creates a graph with the correct size

        for(int i=0;i<int(graph.size());i++){
            TEST_CHECK(graph[i].size()==3);//making sure each node has 3 neighbors
            graph[i].unique();
            TEST_CHECK(graph[i].size()==3);//making sure each node has 3 diferent neighbors.
            for( list<int> ::iterator lit = graph[i].begin();lit!=graph[i].end();lit++){
                TEST_CHECK(*lit!=i); //making sure a node doesn't have itself as a neighbor
            }

        }

}

TEST_LIST = {
    {"test_graph_creation", test_graph_creation},
    {NULL, NULL} 
};
