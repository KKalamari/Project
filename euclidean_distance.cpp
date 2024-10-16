#include <utility>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
using namespace std;

//euclidean distance calculator for every pair of vectors. Brute-force performance,propably obsolete 💀
map <pair <int,int>,float> euclidean_distance(vector<vector<float>>*vec) { 
    double euclidean=0; 
    map <pair <int,int>,float> distances;
    for(int i=0;i<int(vec->size());i++){ //getting the number of total vectors
        for(int j=0; j<int(vec->size());j++){
            if(j==i )
                continue;
            for(int k=0;k<int((*vec)[0].size());k++){ //getting the dimensions of the vector (propably 128)
                euclidean+=sqrt(pow((*vec)[j][k]-(*vec)[i][k],2));
            }
            distances[make_pair(i,j)]=euclidean;
            euclidean=0;
        }
    }
    return distances;
   
    
}

