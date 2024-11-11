#include <vector>
#include<map>
#include<list>
#include<set>
#pragma once
using namespace std;


void pfinder(vector <int> &Rf,map<int,float>&T,int &p);
map <int,float> FindMedoid(vector<vector<float>>DataNodes,int r,set <float>& category_attributes);