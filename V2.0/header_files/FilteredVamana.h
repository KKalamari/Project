#include <iostream>
#include <map>
#include <list>
#include <vector>
#include<set>
#include "FilteredGreedySearch.h"
#include "medoid.h"
#include "FilteredRobust.h"
#include <random>
#pragma once
using namespace std;

map <int,list<int>> FilteredVamanaIndex(vector<vector<double>>&vectormatrix,vector<vector<float>>&DataNodes,int &alpha,int& R,set<float>&category_attributes);