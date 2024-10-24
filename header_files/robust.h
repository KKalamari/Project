#ifndef ROBUSTPRUNE_H
#define ROBUSTPRUNE_H

#include <vector>
#include <unordered_set>
#include <utility> // for std::pair
#include <cstddef> // for size_t

// Function to calculate the Euclidean distance between two points
double distance(const std::pair<double, double>& a, const std::pair<double, double>& b);

// RobustPrune function declaration
void RobustPrune(
    std::vector<std::vector<int>>& graph, 
    const std::vector<std::pair<double, double>>& points, 
    int p, 
    std::unordered_set<int>& candidateSet, 
    double alpha, 
    size_t R // Change R to size_t
);

#endif // ROBUSTPRUNE_H
