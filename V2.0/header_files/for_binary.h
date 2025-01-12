#include <fstream>
#include <map>
#include <list>
#include <iostream>
#include <map>
#include <set>
#include <fstream>
#include <iostream>

using namespace std;
#pragma once
void save_graph_to_binary_set(const std::map<int, std::set<int>>& graph, const std::string& filename);


map<int, list<int>> load_graph_from_binary(const string& filename);