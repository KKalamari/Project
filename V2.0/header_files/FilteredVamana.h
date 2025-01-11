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

map <int,set<int>> FilteredVamanaIndex(vector<vector<double>>&vectormatrix,vector<vector<float>>&DataNodes,double &alpha,int& R,set<float>&category_attributes,map<float,int>&medoids,int L_small);