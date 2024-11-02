#include "robust_ext.h"
using namespace std;

void euclidean_distance(const set<int>& candidateSet, int point, const vector<vector<float>>& vec, map<pair<int, int>, float>& distances) {
    if (vec.empty() || vec[0].empty()) {
        throw invalid_argument("Feature vector 'vec' cannot be empty.");
    }

    for (int candidate : candidateSet) {
        if (candidate == point) continue; // Skip the same point
        double distance = 0;
        for (size_t dim = 0; dim < vec[point].size(); ++dim) {
            distance += pow(vec[point][dim] - vec[candidate][dim], 2);
        }
        distances[{point, candidate}] = sqrt(distance);
    }
}


int pickingP(int point, set<int>& candidateSet, map<pair<int, int>, float>& distances) {
    if (candidateSet.empty()) {
        throw invalid_argument("Candidate set cannot be empty.");
    }

    int closestPoint = -1;
    float minDist = numeric_limits<float>::max();

    for (int candidate : candidateSet) {
        if (candidate == point) continue; // Skip the same point
        float dist = distances[{point, candidate}];
        if (dist < minDist) {
            minDist = dist;
            closestPoint = candidate;
        }
    }

    return closestPoint;
}

void RobustPrune(
    map<int, list<int>>& graph,
    int point,
    vector<vector<float>>& vec,
    set<int>& candidateSet,
    double alpha,
    size_t R
) {
    if (vec.empty() || vec[0].empty()) {
        throw invalid_argument("Feature vector 'vec' cannot be empty.");
    }

    // Ensure 'point' is not in candidate set
    candidateSet.erase(point);
    graph[point].clear();

    // Insert all neighbors of 'point' into candidate set
    for (int neighbor : graph[point]) {
        if (neighbor != point) candidateSet.insert(neighbor);
    }

    // Calculate initial distances from 'point' to candidates
    map<pair<int, int>, float> distances;
    euclidean_distance(candidateSet, point, vec, distances);

    // Perform the pruning
    while (!candidateSet.empty() && graph[point].size() < R) {
        int closestPoint = pickingP(point, candidateSet, distances);
        if (closestPoint == -1) break;

        graph[point].push_back(closestPoint);

        // Calculate distances from closest point to remaining candidates
        map<pair<int, int>, float> distancesToClosestPoint;
        euclidean_distance(candidateSet, closestPoint, vec, distancesToClosestPoint);

        // Prune candidates based on the alpha condition
        for (auto it = candidateSet.begin(); it != candidateSet.end();) {
            int candidate = *it;
            if (alpha * distancesToClosestPoint[{closestPoint, candidate}] <= distances[{point, candidate}]) {
                it = candidateSet.erase(it); // Erase and advance the iterator
            } else {
                ++it; // Only advance if not erasing
            }
        }
    }
}

