#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "acutest.h" 
#include <cmath>

using namespace std;

void modify_neighbors(int p, vector<pair<double, double>>& points, set<int>& out_neighbors, vector<int>& V, double alpha, int R);

void test_modify_neighbors_basic() {
    vector<pair<double, double>> points = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};
    set<int> out_neighbors;
    vector<int> V = {1, 2, 3}; // Candidates are the last three points
    int p = 0; // The point at (0, 0)
    double alpha = 1.0;
    int R = 2; // We want 2 neighbors

    modify_neighbors(p, points, out_neighbors, V, alpha, R);

    // Check if out_neighbors contains the expected indices
    TEST_CHECK(out_neighbors.size() == 2);
    TEST_CHECK(out_neighbors.count(1) > 0 || out_neighbors.count(2) > 0);
}

void test_modify_neighbors_with_alpha() {
    vector<pair<double, double>> points = {{0, 0}, {1, 1}, {2, 2}, {3, 3}};
    set<int> out_neighbors;
    vector<int> V = {1, 2, 3};
    int p = 0;
    double alpha = 0.5; // Adjust alpha to see if it affects neighbor selection
    int R = 2;

    modify_neighbors(p, points, out_neighbors, V, alpha, R);

    // Here we expect to get both 1 and 2 since alpha allows it
    TEST_CHECK(out_neighbors.size() == 2);
    TEST_CHECK(out_neighbors.count(1) > 0);
    TEST_CHECK(out_neighbors.count(2) > 0);
}

void test_modify_neighbors_edge_case() {
    vector<pair<double, double>> points = {{0, 0}};
    set<int> out_neighbors;
    vector<int> V; // No candidates
    int p = 0; // Only one point
    double alpha = 1.0;
    int R = 2;

    modify_neighbors(p, points, out_neighbors, V, alpha, R);

    // Expect no neighbors found
    TEST_CHECK(out_neighbors.empty());
}

void test_modify_neighbors_exact_limit() {
    vector<pair<double, double>> points = {{0, 0}, {1, 1}, {1, 2}, {2, 1}};
    set<int> out_neighbors;
    vector<int> V = {1, 2, 3};
    int p = 0; // Point (0, 0)
    double alpha = 1.0;
    int R = 2; // We want exactly 2 neighbors

    modify_neighbors(p, points, out_neighbors, V, alpha, R);

    // Check that we have exactly 2 neighbors
    TEST_CHECK(out_neighbors.size() == 2);
    TEST_CHECK(out_neighbors.count(1) > 0 || out_neighbors.count(2) > 0);
}

TEST_LIST = {
    { "test_modify_neighbors_basic", test_modify_neighbors_basic },
    { "test_modify_neighbors_with_alpha", test_modify_neighbors_with_alpha },
    { "test_modify_neighbors_edge_case", test_modify_neighbors_edge_case },
    { "test_modify_neighbors_exact_limit", test_modify_neighbors_exact_limit },
    { nullptr, nullptr }
};

