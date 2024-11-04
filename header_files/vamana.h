#include <vector>
#include "robust_ext.h"
#include "euclidean_distance.h"
#include "graph_creation.h"
#include "greedysearch.h"
#include <unordered_set>
#include <algorithm>
#include <random>
#include <iostream>
#include <set>

#pragma once
using namespace std;

//finds the medoid
int medoid(vector<vector<float>>&vec);

//implements vamana algorithm
map<int,list<int>> vamana_index_algorithm(vector<vector<float>>&vec, int &R,int& medoid_node,int &L_sizelist, int& a,vector<vector<double>>& vecmatrix,vector<vector<double>>& querymatrix  );