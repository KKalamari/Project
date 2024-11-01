#include <utility>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <list>
using namespace std;

void euclidean_distance(list<int>& Pneighbors,vector<vector<float>>&vec,vector<float>query_point,map  <int,double>&distances) { 
    double euclidean=0; 
    for(list <int> ::iterator lit=Pneighbors.begin();lit!=Pneighbors.end();lit++){
        for(int i=0; i<int(Pneighbors.size());i++){
            if(vec[*lit]==query_point)
                continue;
            for(int j=0; j<int(vec[i].size());j++){ //calculating  distance for each dimension
                euclidean+=pow(query_point[j]-vec[*lit][j],2);
            }
            distances[*lit]=sqrt(euclidean);
        }

    }
}
    
    
    
    // for(int i=0;i<int(vec.size());i++){ //getting the number of total vectors
    //     for(int j=0; j<int(vec[i].size());j++){
    //         if(vec[i]==query_point )
    //             continue;
    //         euclidean+=pow(query_point[j] - vec[i][j], 2);
    //     }
    //     distances[i]=euclidean;
    //     euclidean=0;
    // }
   
    



// double euclidean_distance(const std::vector<float>& point1, const std::vector<float>& point2) {
//     double distance = 0.0;
//     for (int k = 0; k < int(point1.size()); k++) {
//         distance += pow(point1[k] - point2[k], 2);
//     }
//     return distance;
// }





