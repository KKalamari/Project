#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;
vector<vector<float>> reading_fvecs(const char* filename,int bounda,int boundb);
vector<vector<int>> reading_ivecs(const char* filename,int bounda,int boundb);