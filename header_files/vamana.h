#include <iostream>
#include <vector>
#include "euclidean_distance.h"
#include "greedysearch.h"

#pragma once
using namespace std;

int medoid(vector<vector<float>>&vec);
map<int,list<int>> vamana_index_algorithm(vector<vector<float>>&vec, int &R,int& medoid_node  );