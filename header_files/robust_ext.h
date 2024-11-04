
#pragma once
#include <map>
#include <vector>
#include <list>
#include <iterator>
#include <utility>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include "greedysearch.h"

using namespace std;
void euclidean_distance( set<int>& candidateSet, int point, vector<vector<float>>& vec, map<pair<int, int>, float>& distances);
int pickingP(int point, std::set<int>& candidate_set, std::map<std::pair<int, int>, float>& distances);
void RobustPrune(
    std::map<int, std::list<int>>& graph,
    int point,
    std::vector<std::vector<float>>& vec,
    std::set<int>& candidateSet,
    double alpha,
    size_t R
);
