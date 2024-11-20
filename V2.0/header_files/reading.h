#include <iostream>
#include <vector>
#include <set>
#pragma once
using namespace std;

set<float>ReadBin(const string &file_path,
            int num_dimensions,
            std::vector<std::vector<float>> &data);

             