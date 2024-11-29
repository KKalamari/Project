 

#ifndef STITCHED_VAMANA_H
#define STITCHED_VAMANA_H

#include <vector>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <random>
#include <algorithm>
#include <limits>
#include "FilteredRobust.h"
#include "vamana.h"  

using namespace std;

map<int, set<int>> StitchedVamana(
    vector<vector<float>>& vec,              // Input vectors
    map<float, set<int>>& labelGroups,       // Label groups as map<float, set<int>>
    double alpha,                            // Parameter for pruning
    int Rsmall,                              // Parameter for small graph
    int Lsmall,                              // Parameter for graph construction
    int Rstitched,                           // Parameter for stitched graph
    vector<vector<double>>& vecmatrix        // Precomputed matrix
);

#endif

