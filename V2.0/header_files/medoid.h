#include <iostream>
#include<map>
#include <vector>
#include <list>
#include <set>
#include <random>
#include <algorithm>
#pragma once
using namespace std;


void pfinder(vector <int> &Rf,map<int,float>&T,int &p);
map <float,int> FindMedoid(vector<vector<float>>DataNodes,int r,set <float>& category_attributes);