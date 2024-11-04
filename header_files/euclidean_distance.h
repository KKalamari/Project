#include <utility>
#include <iostream>
#include <map>
#include <vector>

#include <list>
using namespace std;
#pragma once
void euclidean_distance(list<int>& Pneighbors,vector<vector<float>>&vec,vector<float>query_point,map  <int,double>&distances);
void euclidean_distance_of_database(vector<vector<float>>& vec, vector <vector<double>> &matrix);
void euclidean_distance_of_queries(vector<vector<float>>& vec, vector<vector<float>> &queries , vector <vector<double>> &matrix);