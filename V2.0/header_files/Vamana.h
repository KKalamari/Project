#include <vector>
#include "Robust_ext.h"
#include "GreedySearch.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <set>
#pragma once
using namespace std;


map<int, set<int>> graph_creation(list<int>& labeled_nodes, int R);

map <int, set<int>> vamana_index_algorithm(map<float,list<int>>&labeled_nodes,float filters,double a,int& R_small,int &L_small,
vector<vector<double>>& vecmatrix,
map<float,int> M,int R , int L_sizelist);