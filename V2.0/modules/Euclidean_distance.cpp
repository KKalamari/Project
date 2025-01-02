#include "Euclidean_distance.h"

//function that calculates the distance between all of the nodes

int mapping_indexes(int& i,int& j, int& n ){
    return n * i - (i-1)*i/2 + (j-i); //https://stackoverflow.com/questions/34804216/multiplying-upper-triangular-matrix-stored-in-1d-array-alogrithm
}

int matrix_to_triangular(int& i,int& j, int& n ){
    if(i>j)
        swap(i,j);
    return n * i - (i-1)*i/2 + (j-i); //https://stackoverflow.com/questions/34804216/multiplying-upper-triangular-matrix-stored-in-1d-array-alogrithm
}



void euclidean_distance_of_database(vector<vector<float>> &vec, vector<double> &matrix)
{
    int n = int(vec.size());
    for (int i = 0; i <n; i++) {
        for (int j = i + 1; j < n; j++) {
            double euclidean = 0;  //rset for each new pair (i, j)

            for (int k = 2; k < int(vec[k].size()); k++) { //we don't consider the first 2 dimensions.
                euclidean += pow(vec[i][k] - vec[j][k], 2);//use vec for both i and j
            }

            double dist = sqrt(euclidean);
            matrix[mapping_indexes(i,j,n)] = dist;

        }
    }
}

//function tha calculates the distance between the nodes and the queries
void euclidean_distance_of_queries(vector<vector<float>>& vec, vector<vector<float>> &queries, vector<vector<double>> &matrix) {
    int n=vec.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < int(queries.size()); j++) {
            double euclidean = 0;  //reset for each query
            for (int k = 2; k < n; k++) {
                euclidean += pow(vec[i][k] - queries[j][k+2], 2); //we don't consider the first 2 dimensions of data and 4 dimensions of query
            }
            matrix[i][j] = sqrt(euclidean);
        }
        
    }
}