#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cfloat>
#include <list>
#pragma once
using namespace std;

// Comparator για το set που συγκρίνει τα στοιχεία με βάση την απόσταση τους από το query
struct DistanceComparator {
    vector<vector<double>> querymatrix;
    int query;

    DistanceComparator(const vector<vector<double>>& matrix, int q) : querymatrix(matrix), query(q) {}

    // Ensure the compiler generates a copy constructor if needed.
    DistanceComparator(const DistanceComparator& other) = default;

    bool operator()(int a, int b) const {
        return querymatrix[a][query] < querymatrix[b][query];
    }
};

void pickingP(int &p,set <int,DistanceComparator>&L,set<int,DistanceComparator>&V,vector <vector <double>>querymatrix,int query);

pair <vector<int>,vector<int>> FilteredGreedy(map<int,list<int>>&graph,int xq,int knn,int L_sizelist,map <float,int> &M,vector<float>&Fq,vector<vector<double>> querymatrix,vector<vector<float>>&dataset);





