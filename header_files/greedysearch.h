#include <map>
#include <list>
#include <iostream>
#include <vector>
#include <set>
#pragma once
using namespace std;

bool unexplored_nodes(list <int>L,list <int>visited);
bool unexplored_node(int node, const list<int> visited);
void addtoL(list <int> neighbors,list <int> &L,vector<vector<double>>& vecmatrix,int Lsizelist,int s,vector<vector<float>>&vec,int&query);
pair <set <int>,set <int>> greedysearch( vector<vector<float>>& vec,map <int, list<int>>& graph,int &,int& query_point,int &k_neigh,int &L_sizelist,vector<vector<double>>& querymatrix);
