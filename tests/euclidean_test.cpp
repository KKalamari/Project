#include <iostream>
#include <algorithm>
#include "acutest.h"  // Include Acutest
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "euclidean_distance.h"
#include <math.h>

using namespace std;

void test_euclidean(){
    vector<vector<float>> vec(1);
    vec[0]={8,45,765};
    vector<float>query_point={456,43,64  };

    
    float real_euclidean_distance= 831.931;
    map<int,double>distance ;
    float tolerance = 0.1;

    euclidean_distance(vec,query_point,distance);
    TEST_CHECK(fabs(distance[0] - real_euclidean_distance) < tolerance); //https://stackoverflow.com/questions/17333/how-do-you-compare-float-and-double-while-accounting-for-precision-loss
}


TEST_LIST = {
    {"test_euclidean", test_euclidean},
    {NULL, NULL}  // Terminate the test list
};