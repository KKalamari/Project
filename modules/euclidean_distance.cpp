#include <utility>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <list>
#include "euclidean_distance.h"
using namespace std;



void euclidean_distance_of_database(vector<vector<float>> &vec, vector<vector<double>> &matrix)
{
    for (int i = 0; i < int(vec.size()); i++) {
        for (int j = i + 1; j < int(vec.size()); j++) {
            double euclidean = 0;  // Reset for each new pair (i, j)

            for (int k = 0; k < int(vec[k].size()); k++) {
                euclidean += pow(vec[i][k] - vec[j][k], 2); // Use vec for both i and j
            }

            double dist = sqrt(euclidean);
            matrix[i][j] = dist;
            matrix[j][i] = dist; // Symmetric assignment
        }
    }
}

void euclidean_distance_of_queries(vector<vector<float>>& vec, vector<vector<float>> &queries, vector<vector<double>> &matrix) {
    for (int i = 0; i < int(vec.size()); i++) {
        for (int j = 0; j < int(queries.size()); j++) {
            double euclidean = 0;  // Reset for each query
            for (int k = 0; k < int(vec[i].size()); k++) {
                euclidean += pow(vec[i][k] - queries[j][k], 2);
            }
            matrix[i][j] = sqrt(euclidean);
        }
        
        
    }
}



// void euclidean_for_everything(vector<vector<float>>&vec,int**){
//     int vector_size=int (vec.size());
//     for(int i=0;i<vector_size;i++){
//         for(int j=)
//     }

// }

    
    
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





