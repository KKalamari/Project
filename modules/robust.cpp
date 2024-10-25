#include "robust.h"
#include <cmath>
#include <limits>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

double eucledian(const pair<double, double>& a, const pair<double, double>& b) 
{
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

void Robust(
    vector<vector<int>>& graph,
    const vector<pair<double, double>>& points,
    int p,
    unordered_set<int>& candidateset,
    double alpha,
    size_t R
) 

{
    //adding every neighbor of p in the candidate Set
    for (int neighbor : graph[p]) 
    {
        candidateset.insert(neighbor);
    }

    unordered_set<int> newneighbors;

    while (!candidateset.empty() && newneighbors.size() < R) 
    {
        int closestpoint = -1;
        double mindistance = numeric_limits<double>::max();

        for (int candidate : candidateset) 
        {
            double dist = eucledian(points[p], points[candidate]);
            if (dist < mindistance) 
            {
                mindistance = dist;
                closestpoint = candidate;
            }
        }

        if (closestpoint == -1) 
        {
            break; 
        }

        newneighbors.insert(closestpoint);
        //candidateset.erase(closestpoint);

        for (auto it = candidateset.begin(); it != candidateset.end();) 
        {
            double distToClosest = eucledian(points[closestpoint], points[*it]);
            double distToP = eucledian(points[p], points[*it]);

            if (alpha * distToClosest <= distToP) 
            {
                it = candidateset.erase(it); 
            } else 
            {
                ++it;
            }
        }
    }

    graph[p].clear();

    for (int neighbor : newneighbors) 
    {
        graph[p].push_back(neighbor);
    }

}

