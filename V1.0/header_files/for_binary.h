#include <fstream>
#include <map>
#include <list>
#include <iostream>
using namespace std;

void save_graph_to_binary(const map<int, list<int>>& graph, const string& filename);


map<int, list<int>> load_graph_from_binary(const string& filename);