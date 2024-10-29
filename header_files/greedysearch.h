#include <map>
#include <list>
#include <iostream>
#include <vector>
#pragma once
using namespace std;

bool unexplored_nodes(list <int>L,list <int>visited);
bool unexplored_node(int,list <int> visited);
void addtoL(list <int> neighbors,list <int> &L,map <int,double>distances,int Lsizelist);
pair <set <int>,set <int>> greedysearch( map <int, list<int>>& s,vector<float> query_point,int k_neigh,int L_sizelist,map <int,double>distances);
