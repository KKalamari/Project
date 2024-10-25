
#include <vector>
#include <list>
#include <map>
#include <unordered_set>
#include <utility> 
#include <cstddef> 
using namespace std;

double eucledian(const pair<double, double>& a, const pair<double, double>& b);

void Robust(
    vector<vector<int>>& graph, 
    const vector<pair<double, double>>& points, 
    int p, 
    unordered_set<int>& candidateSet, 
    double alpha, 
    size_t R 
);
