#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;


map<int,set<int>> StitchedVamana(vector <vector<float>>& DataNodes,
set<float> &category_attributes,
double a,int L_small,int R_small, int R_stitched
,vector<double>& vecmatrix,
map<float,int> M);