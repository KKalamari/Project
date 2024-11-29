
#pragma once
#include <set>
#include <map>
#include <vector>
#include <list>
#include <cmath>
#include <iterator>
#include <utility>
#include <algorithm>
#include "euclidean_distance.h"
using namespace std;
//void euclidean_distance( set<int>& candidateSet, int point, vector<vector<float>>& vec, map<pair<int, int>, float>& distances);

int pickingP(int point, set<int>& candidate_set, vector<vector<double>>& distances); //picks the closest p

//implements robust prune
void RobustPrune(
    map<int, list<int>>& graph,
    int point,
    set<int>& candidateSet,
    double alpha,
    size_t R,
    vector<vector<double>>& vecmatrix
);
