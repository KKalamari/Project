#include <iostream>
#include <algorithm>
#include "acutest.h"  
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "euclidean_distance.h"
#include <math.h>
#include <list>
using namespace std;

//Calculating the euclidean distance of a node from a query point using euclidean_distance _of _queries
void test_euclidean(){
    vector<vector<float>> vec(1);
    vec[0]={8,45,765};
    vector<vector<float>>query_point={{456,43,64  }};

    list <int> Pneighbor={0};
    float real_euclidean_distance= 831.931;
    map<int,double>distances ;
    float tolerance = 0.1;
    vector<vector<double>> queriesmatrix(vec.size(),vector<double>(query_point.size()));
    euclidean_distance_of_queries(vec,query_point,queriesmatrix);
    TEST_CHECK(fabs(queriesmatrix[0][0] - real_euclidean_distance) < tolerance); //https://stackoverflow.com/questions/17333/how-do-you-compare-float-and-double-while-accounting-for-precision-loss
}


TEST_LIST = {
    {"test_euclidean", test_euclidean},
    {NULL, NULL}  // Terminate the test list
};