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


void pickingP(int &p,set <int,DistanceComparator>&L,set<int,DistanceComparator>&V,vector <vector <double>>querymatrix,int query);

pair <vector<int>,vector<int>> FilteredGreedy(map<int,list<int>>&graph,int xq,int knn,int L_sizelist,map <float,int> &M,vector<float>&Fq,vector<vector<double>> querymatrix,vector<vector<float>>&dataset);





