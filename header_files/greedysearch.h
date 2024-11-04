#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include "graph_creation.h"
#include "euclidean_distance.h"
#include <reading.h>
#include <list>
#include <map>
#include <utility>
#pragma once
using namespace std;

bool unexplored_nodes(list <int>L,list <int>visited);
bool unexplored_node(int node, const list<int> visited);
void addtoL(list <int> neighbors,list <int> &L,map <int,double>&distances,int Lsizelist,int s,vector<vector<float>>&vec,vector<float>&query);
pair <set <int>,set <int>> greedysearch( vector<vector<float>>& vec,map <int, list<int>>& graph,int &,vector<float> query_point,int k_neigh,int L_sizelist);
