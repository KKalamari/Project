#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#pragma once
using namespace std;
//functions that read fvecs and ivecs files
vector<vector<float>> reading_fvecs(const char* filename,int bounda,int boundb);
vector<vector<int>> reading_ivecs(const char* filename,int bounda,int boundb);