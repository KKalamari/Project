#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <cfloat>
#include "FilteredGreedySearch.h"
using namespace std;

void pickingp_star(int& p_star,int&p,vector<vector<double>> vecmatrix,set<int,DistanceComparator> &V);
void FilteredRobustPrune(map <int,list<int>>&graph,int &p,set<int,DistanceComparator> &V,int &alpha,int&R,vector<vector<double>> &vectormatrix,vector<vector<float>>&dataset);