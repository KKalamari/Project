#include "Euclidean_distance.h"
#include <immintrin.h>
#include <omp.h>
//function that calculates the distance between all of the nodes

void euclidean_distance_of_database(vector<vector<float>>& vec, vector<vector<double>>& matrix,int thread_num) {
    int count = thread_num;
    int n=vec.size();
    int blocksize =32; //gonna be used for tiling method

    #pragma omp parallel for num_threads(count) schedule(dynamic)

    for(int bi=0; bi < n; bi += blocksize){
        for (int bj = bi; bj < n;bj+=blocksize){
            for(int i =bi; i <min(bi+blocksize,n);i++){ 
                for(int j = max(i+1,bj); j<min(bj+blocksize, n);j++){        
    
                    __m256 accumulator = _mm256_setzero_ps();
                    int k;
                    
                    //processing 8 elements at once starting from k=2
                    for (k = 2; k + 7 < vec[i].size(); k += 8) {
                        __m256 vi = _mm256_loadu_ps(&vec[i][k]);
                        __m256 vj = _mm256_loadu_ps(&vec[j][k]);
                        
                        __m256 diff = _mm256_sub_ps(vi, vj);
                        accumulator = _mm256_fmadd_ps(diff, diff, accumulator);
                    }
                    
                    // Sum the accumulated values
                    float tmp[8];
                    _mm256_storeu_ps(tmp, accumulator);
                    float euclidean = 0.0f;
                    for (int m = 0; m < 8; m++) {
                        euclidean += tmp[m];
                    }
                    
                    // Handle remaining elements
                    for (k; k < vec[i].size(); k++) {
                        float diff = vec[i][k] - vec[j][k];
                        euclidean += diff * diff;
                    }
                    
                    matrix[i][j] = euclidean;
                    // matrix[j][i] = euclidean;
                }
            }
        }
    }
 // Write the symmetric values to improve memory locality
    #pragma omp parallel for num_threads(count) schedule(dynamic)
    for (int bi = 0; bi < n; bi += blocksize) {
        for (int bj = bi; bj < n; bj += blocksize) {
            for (int i = bi; i < min(bi + blocksize, n); i++) { // min(bi + blockSize, n) in order to not pass the vec.size()
                for (int j = max(i + 1, bj); j < min(bj + blocksize, n); j++) {
                    matrix[j][i] = matrix[i][j];
                }
            }
        }
    }
}


















//function tha calculates the distance between the nodes and the queries
void euclidean_distance_of_queries(vector<vector<float>>& vec, vector<vector<float>> &queries, vector<vector<double>> &matrix,int thread_num) {
    // #pragma omp parallel for schedule(static)
    int count = thread_num;
    #pragma omp parallel for num_threads(count) schedule(dynamic)
    for (int i = 0; i < int(vec.size()); i++) {
        for (int j = 0; j < int(queries.size()); j++) {
            double euclidean = 0;  //reset for each query
            int k;
            __m256 accumulator = _mm256_setzero_ps();
            
            for ( k = 2; k +7< int(vec[i].size()); k+=8) {
                __m256 vi = _mm256_loadu_ps(&vec[i][k]);
                __m256 vj = _mm256_loadu_ps(&vec[j][k]);

                __m256 diff = _mm256_sub_ps(vi,vj);
                accumulator = _mm256_fmadd_ps(diff,diff,accumulator);
                
                }
            float temp[8];
            _mm256_storeu_ps(temp, accumulator);

            for(int m=0;m<7;m++)
                euclidean+=temp[m];
            
            for(k;k<vec[i].size();k++){
                float distance = vec[i][k] - vec[j][k];
                euclidean+=distance*distance;
            }
            matrix[i][j]=euclidean;
        }
        
        
    }
}