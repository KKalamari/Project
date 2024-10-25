#include <utility>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
using namespace std;

void euclidean_distance(vector<vector<float>>&vec,vector<float>query_point,map  <int,float>&distances) { 
    double euclidean=0; 
    for(int i=0;i<int(vec.size());i++){ //getting the number of total vectors
        for(int j=0; j<int(vec[i].size());j++){
            if(vec[i]==query_point )
                continue;
            euclidean+=pow(query_point[j] - vec[i][j], 2);
        }
        euclidean=sqrt(euclidean);
        distances[i]=euclidean;
        euclidean=0;
    }
   
    
}





