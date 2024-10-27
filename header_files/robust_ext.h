#include <vector>
#include <list>
#include <map>
#include <set>
#pragma once
using namespace std;

void euclidean_distance(set <int> candidate_set, int point,vector<vector<float>>vec,map<pair <int,int>,float>&distances);
int pickingP(int point,set <int> candidate_set,map<pair <int,int>,float> &distances );
void RobustPrune(
    map<int,list<int>>& graph,
    int point,
    vector<vector<float>> &vec, //distances
    set<int>& candidateSet, //V
    double alpha,
    size_t R
);
