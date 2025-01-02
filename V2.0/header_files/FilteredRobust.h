#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <cfloat>
#include "FilteredGreedySearch.h"
#pragma once
using namespace std;

void pickingp_star(int& p_star,int&p,vector<double>& vecmatrix,set<int,DistanceComparator> &V);
int FilteredRobustPrune(map <int,set<int>>&graph,int &p,set<int> &V,double &alpha,int&R,vector<double> &vectormatrix,vector<vector<float>>&dataset);