#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <list>
#include <map>
#include <utility>
#include <set>
#pragma once
using namespace std;

//ensuring that L contains at leasτ one node which haven't been already explored.
bool unexplored_nodes(list <int>L,list <int>visited); 

//the same logic with the above just for a specific node
bool unexplored_node(int node, const list<int> visited);

//adding the neighbors of the node which P contains in a sorted way.Also prunes the nodes when overextending the L_sizelist.
void addtoL(set <int> neighbors,list <int> &L,vector<vector<double>>& vecmatrix,int Lsizelist,int&query);

//implements the greedy algorithm
pair <set <int>,set <int>> greedysearch(map <int, set<int>>& graph,int &,int& query_point,int &k_neigh,int &L_sizelist,vector<vector<double>>& querymatrix);
