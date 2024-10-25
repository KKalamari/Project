#include <acutest.h>
#include "robust.h"
#include <vector>
#include <unordered_set>
#include <utility>
#include <cmath>
#include <iostream>
using namespace std;

bool compareGraphs(const vector<vector<int>>& g1, const vector<vector<int>>& g2) {
    if (g1.size() != g2.size()) return false;
    for (size_t i = 0; i < g1.size(); ++i) {
        if (g1[i].size() != g2[i].size()) return false;
        for (size_t j = 0; j < g1[i].size(); ++j) {
            if (g1[i][j] != g2[i][j]) return false;
        }
    }
    return true;
}

// Test case: basic pruning with a simple graph
void test_basic_pruning(void) {
    // Create a simple graph: 4 nodes, fully connected initially
    vector<vector<int>> graph = {
        {1, 2, 3},  // Neighbors of node 0
        {0, 2, 3},  // Neighbors of node 1
        {0, 1, 3},  // Neighbors of node 2
        {0, 1, 2}   // Neighbors of node 3
    };
    
    // Corresponding 2D points (coordinates for each node)
    vector<pair<double, double>> points = {
        {0.0, 0.0},  // Point for node 0
        {1.0, 0.0},  // Point for node 1
        {0.0, 1.0},  // Point for node 2
        {1.0, 1.0}   // Point for node 3
    };
    
    unordered_set<int> candidateSet;
    double alpha = 1.5; // Set alpha
    size_t R = 2;       // Max number of neighbors after pruning

    // Apply the RobustPrune algorithm to node 0
    Robust(graph, points, 0, candidateSet, alpha, R);

    // Expected result after pruning (only 2 closest neighbors should be kept)
    vector<vector<int>> expectedGraph = {
        {1, 2},    // Node 0 should have only 2 neighbors left
        {0, 2, 3}, // Others remain unchanged
        {0, 1, 3},
        {0, 1, 2}
    };

    TEST_CHECK(compareGraphs(graph, expectedGraph));
}

// Test case: pruning with higher alpha to relax pruning
void test_high_alpha_pruning(void) {
    // Same graph setup as before
    vector<vector<int>> graph = {
        {1, 2, 3},
        {0, 2, 3},
        {0, 1, 3},
        {0, 1, 2}
    };

    // Same points as before
    vector<pair<double, double>> points = {
        {0.0, 0.0},  
        {1.0, 0.0},  
        {0.0, 1.0},  
        {1.0, 1.0}  
    };

    unordered_set<int> candidateSet;
    double alpha = 3.0; // Higher alpha, relaxed pruning
    size_t R = 2;       // Max number of neighbors after pruning

    // Apply RobustPrune algorithm to node 0
    Robust(graph, points, 0, candidateSet, alpha, R);

    // Expected result: the pruning is more relaxed with higher alpha
    vector<vector<int>> expectedGraph = {
        {1, 2},    // Node 0 should still have only 2 neighbors due to R
        {0, 2, 3}, 
        {0, 1, 3}, 
        {0, 1, 2}  
    };

    TEST_CHECK(compareGraphs(graph, expectedGraph));
}


// Registering the test cases with Acutest
TEST_LIST = {
    {"Basic Pruning", test_basic_pruning},
    {"High Alpha Pruning", test_high_alpha_pruning},
   // {"Low Alpha Pruning", test_low_alpha_pruning},
    {NULL, NULL} // End of test list
};
