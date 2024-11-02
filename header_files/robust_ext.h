
#pragma once
#include <set>
#include <map>
#include <vector>
#include <list>
#include <cmath>
#include <iterator>
#include <utility>
#include <algorithm>

void euclidean_distance(const std::set<int>& candidateSet, int point, const std::vector<std::vector<float>>& vec, std::map<std::pair<int, int>, float>& distances);
int pickingP(int point, std::set<int>& candidate_set, std::map<std::pair<int, int>, float>& distances);
void RobustPrune(
    std::map<int, std::list<int>>& graph,
    int point,
    std::vector<std::vector<float>>& vec,
    std::set<int>& candidateSet,
    double alpha,
    size_t R
);
