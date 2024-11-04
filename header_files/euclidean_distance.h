#include <utility>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <list>
using namespace std;
#pragma once
void euclidean_distance_of_database(vector<vector<float>>& vec, vector <vector<double>> &matrix); //2d vec matrix dist of each node with everyone else
void euclidean_distance_of_queries(vector<vector<float>>& vec, vector<vector<float>> &queries , vector <vector<double>> &matrix);//2d matric with the distances of each node with every query 