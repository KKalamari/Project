#include <utility>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <list>
using namespace std;

void euclidean_distance(list<int>& Pneighbors, vector<vector<float>>& vec, vector<float> query_point, map<int, double>& distances) { 
    for (list<int>::iterator lit = Pneighbors.begin(); lit != Pneighbors.end(); lit++) { 
        double euclidean = 0; 
        for (int j = 0; j < int(vec[*lit].size()); j++) { //calculating distance for each dimension
            euclidean += pow(query_point[j] - vec[*lit][j], 2);
        }
        distances[*lit] = sqrt(euclidean); //storing the distance in the map
    }
}




