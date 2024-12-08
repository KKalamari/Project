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

struct DistanceComparator {
    const vector<vector<double>>& querymatrix; 
    int query;

    // Constructor that accepts a reference to the matrix
    DistanceComparator(const vector<vector<double>>& matrix, int q) 
        : querymatrix(matrix), query(q) {}


    bool operator()(int a, int b) const {
        if (a >= querymatrix.size() || b >= querymatrix.size() || query >= querymatrix[0].size()) {
            throw std::out_of_range("Index out of bounds in DistanceComparator.");
        }
        return querymatrix[a][query] < querymatrix[b][query];
    }
};


//void pickingP(int &p,set <pair<double,int>>&L,set<int>&V,vector <vector <double>>&querymatrix,int query);

bool unexplored_nodes(const set<pair<double, int>>& L, const set<int>& visited);

pair <set<pair<double,int>>,set<int>> FilteredGreedy(map<int,set<int>>&graph,int xq,int knn,int L_sizelist,map <float,int> &M,vector<float>&Fq,vector<vector<double>>& querymatrix,vector<vector<float>>&dataset,set<float>&category_attribuytes);





