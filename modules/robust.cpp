#include "robust.h"
#include <cmath>
#include <limits>
#include <iostream>

double distance(const std::pair<double, double>& a, const std::pair<double, double>& b) 
{
    return std::sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

void RobustPrune(
    std::vector<std::vector<int>>& graph,
    const std::vector<std::pair<double, double>>& points,
    int p,
    std::unordered_set<int>& candidateSet,
    double alpha,
    size_t R
) 
{
    for (int neighbor : graph[p]) 
    {
        candidateSet.insert(neighbor);
    }
    candidateSet.erase(p); 

    std::unordered_set<int> newNeighbors;

    while (!candidateSet.empty() && newNeighbors.size() < R) 
    {
        int closestPoint = -1;
        double minDistance = std::numeric_limits<double>::max();

        for (int candidate : candidateSet) 
        {
            double dist = distance(points[p], points[candidate]);
            if (dist < minDistance) 
            {
                minDistance = dist;
                closestPoint = candidate;
            }
        }

        if (closestPoint == -1) 
        {
            break; 
        }

        newNeighbors.insert(closestPoint);
        candidateSet.erase(closestPoint);

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

