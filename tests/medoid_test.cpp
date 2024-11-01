#include "acutest.h"
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <iostream>
#include <set>
#include "vamana.h"



void testing_modoiod(){
    vector<vector<float>>vec={
        {1,2,3,4},
        {4,5,6,7},
        {1,1,1,1},
        {2,3,5,7},
        {8,6,7,5},
        {3,3,3,3},
        {6,6,6,6},
        {5,8,5,3}
};

int medoid_node= medoid(vec);
cout <<"medoid_node is: " <<medoid_node<<endl;
TEST_CHECK(medoid_node==5);
}

void vamana_testing(){
    

    vector<vector<float>>vec={
        {1,2,3,4},
        {4,5,6,7},
        {1,1,1,1},
        {2,3,5,7},
        {8,6,7,5},
        {3,3,3,3},
        {6,6,6,6},
        {5,8,5,3}
};
    
    
    vamana_index_algorithm(vec,2);

}

TEST_LIST{
    "testing_medoid",testing_modoiod,
    "vamana_testing",vamana_testing,
    {NULL,NULL}
};
