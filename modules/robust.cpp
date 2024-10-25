#include "robust.h"
#include <cmath>
#include <limits>
#include <iostream>


using namespace std;

double distance(const pair<double, double>& a, const pair<double, double>& b) 
{
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

void RobustPrune(
    map<int,list<int>>& graph,
    const vector<pair<double, double>>& points,
    int p,
    unordered_set<int>& candidateSet, //v
    double alpha,
    size_t R
) 

{
    //adding every neighbor of p in the candidate Set
    for (int neighbor : graph[p]) 
    {
        candidateSet.insert(neighbor);

        graph[p].remove(neighbor);// removing every neighbor from p
    }
//    candidateSet.erase(p); 

    unordered_set<int> newNeighbors;

    while (!candidateSet.empty() && newNeighbors.size() < R) 
    {
        int closestPoint = -1; //τι είναι αυτό;
        double minDistance = numeric_limits<double>::max();

        for (int candidate : candidateSet) 
        {
            double dist = distance(points[p], points[candidate]);
            if (dist < minDistance) 
            {
                minDistance = dist;
                closestPoint = candidate; //p
            }
        }

        if (closestPoint == -1) 
        {
            break; 
        }

        newNeighbors.insert(closestPoint);
        // candidateSet.erase(closestPoint); //γιατί κάνουμε erase εδώ;

        for (auto it = candidateSet.begin(); it != candidateSet.end();) 
        {
            double distToClosest = distance(points[closestPoint], points[*it]);
            double distToP = distance(points[p], points[*it]);

            if (alpha * distToClosest <= distToP) 
            {
                it = candidateSet.erase(it); 
            } else 
            {
                ++it;
            }
        }
    }

    graph[p].clear();

    for (int neighbor : newNeighbors) 
    {
        graph[p].push_back(neighbor);
    }
    
}

