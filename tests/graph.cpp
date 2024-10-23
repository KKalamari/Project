// greedy.cpp
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "acutest.h"  // Include Acutest
#include "graph_creation.h"  // Include the header for graph_creation

using namespace std;

// Test case to verify that the graph was created properly
void test_graph_creation(void) {
    // Set up the test input
    vector<vector<float>> test_vec = { 
        {0.1, 0.2}, {0.3, 0.4}, {0.5, 0.6}, {0.7, 0.8} 
    };  // Example input vector
    int R = 3;  // Example value for R (each node should have 3 neighbors)

    // Create a pointer to the vector
    vector<vector<float>>* ptr_vec = &test_vec;

    // Call the function to create the graph with the pointer
    map<int, set<int>> graph = graph_creation(ptr_vec, R);

    // Check that the graph has the correct number of nodes
    TEST_CHECK(graph.size() == test_vec.size());

    // Check that each node has R neighbors and no self-loops
    for (auto const& node : graph) {
        TEST_CHECK(node.second.size() == static_cast<std::set<int>::size_type>(R));  // Ensure each node has R neighbors

        for (int neighbor : node.second) {
            TEST_CHECK(node.first != neighbor);  // Ensure no self-loops
        }
    }
}

// Test list for Acutest
TEST_LIST = {
    {"test_graph_creation", test_graph_creation},
    {NULL, NULL}  // Terminate the test list
};
