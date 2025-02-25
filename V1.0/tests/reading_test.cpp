#include <iostream>
#include <algorithm>
#include "acutest.h" 
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "reading.h"


using namespace std;
//making sure vectors contain the right float numbers as well as the size
void test_reading(void) {
    vector<vector<float>> vec;
    vec= reading_fvecs("siftsmall_base.fvecs",1,10);
    vector <float> checker_vector= { 0, 16, 35, 5, 32, 31, 14, 10, 11, 78, 55, 10, 45, 83, 11, 6, 14, 57, 102, 75, 20, 8, 3
    , 5, 67, 17, 19, 26, 5, 0, 1, 22, 60, 26, 7, 1, 18, 22, 84, 53, 85, 119, 119, 4, 24, 18, 7, 7, 1, 81, 106, 102, 72, 30,
     6, 0, 9, 1, 9, 119, 72, 1, 4, 33, 119, 29, 6, 1, 0, 1, 14, 52, 119, 30, 3, 0, 0, 55, 92, 111, 2, 5, 4, 9, 
    22, 89, 96, 14, 1, 0, 1, 82, 59, 16, 20, 5, 25, 14, 11, 4, 0, 0, 1, 26, 47, 23, 4, 0, 0, 4, 38, 83, 30
    , 14, 9, 4, 9, 17, 23, 41, 0, 0, 2, 8, 19, 25, 23, 1 }; //based on matlab, this is the containments of the first vector

    
    TEST_CHECK (vec[0]==checker_vector);
    TEST_CHECK(int(vec[0].size())==128);


}

TEST_LIST = {
    {"test_reading", test_reading},
    {NULL, NULL} 
};