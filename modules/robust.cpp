#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <set>
#include <algorithm>
using namespace std;

//euclidean distance between two points
double distance(const pair<double, double>& p1, const pair<double, double>& p2)
{
    return sqrt(pow(p1.first - p2.first, 2) + pow(p1.second - p2.second, 2));
}

//the pseudocode but in cpp?

void modify_neighbors(int p, vector<pair<double, double>>& points, set<int>& out_neighbors, vector<int>& V, double alpha, int R)
{
    set<int> candidate_set(V.begin(), V.end());
    candidate_set.insert(out_neighbors.begin(), out_neighbors.end());
    candidate_set.erase(p);
    out_neighbors.clear();   

    while (!candidate_set.empty())
    {
        int p_star = -1;
        double min_distance = numeric_limits<double>::infinity();
        for (int p_prime : candidate_set)
        {
            double dist = distance(points[p], points[p_prime]);
            if (dist < min_distance)
            {
                min_distance = dist;
                p_star = p_prime;
            }
        }

        out_neighbors.insert(p_star);
        if  (out_neighbors.size() == static_cast<size_t>(R)) break;

        for (auto it = candidate_set.begin(); it != candidate_set.end();)
        {
            int p_prime = *it;
            if (alpha * distance(points[p_star], points[p_prime]) <= distance(points[p], points[p_prime]))
            {
                it = candidate_set.erase(it);
            } else
            {
                ++it;
            }
        }
    }
}