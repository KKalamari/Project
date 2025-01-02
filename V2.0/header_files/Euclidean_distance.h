#include <utility>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <list>
#pragma once
using namespace std;


int mapping_indexes(int& i,int& j, int& n );

void euclidean_distance_of_database(vector<vector<float>> &vec, vector<double> &matrix);

void euclidean_distance_of_queries(vector<vector<float>>& vec, vector<vector<float>>&queries, vector<vector<double>> &matrix);

int matrix_to_triangular(int& i,int& j, int& n );