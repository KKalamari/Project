#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <cfloat>
#pragma once
using namespace std;

// Comparator για το set που συγκρίνει τα στοιχεία με βάση την απόσταση τους από το query
struct DistanceComparator {
    vector<vector<double>> querymatrix;
    int query;

    // Κατασκευαστής για αρχικοποίηση των μεταβλητών σύγκρισης
    DistanceComparator(const vector<vector<double>>& matrix, int q) : querymatrix(matrix), query(q) {}

    bool operator()(int a, int b) const {
        return querymatrix[a][query] < querymatrix[b][query];
    }
};

void pickingP(int &p,set <int,DistanceComparator>&L,set<int,DistanceComparator>&V,vector <vector <double>>querymatrix,int query);

pair <vector<int>,vector<int>> FilteredGreedy(map<int,vector<int>>&graph,int xq,int knn,int L_sizelist,map <float,int> &M,vector<float>&Fq,vector<vector<double>> querymatrix,vector<vector<float>>&dataset);





