#include "euclidean_distance.h"

//function that calculates the distance between all of the nodes

void euclidean_distance_of_database(vector<vector<float>> &vec, vector<vector<double>> &matrix)
{
    for (int i = 0; i < int(vec.size()); i++) {
        for (int j = i + 1; j < int(vec.size()); j++) {
            double euclidean = 0;  //rset for each new pair (i, j)

            for (int k = 2; k < int(vec[k].size()); k++) { //we don't consider the first 2 dimensions.
                euclidean += pow(vec[i][k] - vec[j][k], 2);//use vec for both i and j
            }

            double dist = sqrt(euclidean);
            matrix[i][j] = dist;
            matrix[j][i] = dist; //it's symmetric

        }
    }
}

//function tha calculates the distance between the nodes and the queries
void euclidean_distance_of_queries(vector<vector<float>>& vec, vector<vector<float>> &queries, vector<vector<double>> &matrix) {
    for (int i = 0; i < int(vec.size()); i++) {
        for (int j = 0; j < int(queries.size()); j++) {
            double euclidean = 0;  //reset for each query
            for (int k = 2; k < int(vec[i].size()); k++) {
                euclidean += pow(vec[i][k] - queries[j][k+2], 2); //we don't consider the first 2 dimensions of data and 4 dimensions of query
            }
            matrix[i][j] = sqrt(euclidean);
        }
        
        
    }
}