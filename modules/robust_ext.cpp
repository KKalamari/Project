#include "robust.h"
#include <cmath>
#include <limits>
#include <iostream>
#include <set>
using namespace std;

using namespace std;


double distance(const pair<double, double>& a, const pair<double, double>& b) 
{
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}
bool cmp(int a, int b) {
    return ;
}

void RobustPrune(
    map<int,list<int>>& graph,
    //const vector<pair<double, double>>& points,
    int p,
    unordered_set<int>& candidateSet, //v
    double alpha,
    size_t R
) {

//adding every neighbor of p in the candidate Set
    
    for (int neighbor : graph[p]) 
    {
        candidateSet.insert(neighbor);

        graph[p].remove(neighbor);// removing every neighbor from p
    }

    set <int> new_neighbor;


}