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
        for (int j = 0; j < int(vec[*lit].size()); j++) { // Calculating distance for each dimension
            euclidean += pow(query_point[j] - vec[*lit][j], 2);
        }
        distances[*lit] = sqrt(euclidean); // Storing the distance in the map
    }
}

void euclidean_for_everything(vector<vector<float>>&vec,int**){
    int vector_size=int (vec.size());
    for(int i=0;i<vector_size;i++){
        for(int j=)
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





