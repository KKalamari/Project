#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <list>
#include <map>
#include <utility>
#include <set>
#pragma once
using namespace std;




//implements the greedy algorithm
pair <set<pair<double,int>>,set<int>> greedysearch( map <int, set<int>>& graph,int &s,int& query_point,int &k_neigh,int &L_sizelist,vector<double>&querymatrix);
