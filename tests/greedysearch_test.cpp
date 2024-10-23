#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include "acutest.h"  // Include Acutest
#include "greedysearch.h"

using namespace std;

void test_unexplored_nodes(){
    set <int> L ={0,1,2};
    set <int> V ={1,2,3};
    bool biased_checker=1; //L contains zero which does not exist in V
    bool actual_checker=unexplored_nodes(L,V);
    TEST_CHECK(actual_checker==biased_checker);

    L={0,1,2,3}; //L contains "1 " which does not exist in V
     V={0,2,3};
    actual_checker= unexplored_nodes(L,V);
    TEST_CHECK(actual_checker==biased_checker);

    L={0,1,2}; //contains the "2" which does not exist in V
    V={0,1,3,4};
    actual_checker= unexplored_nodes(L,V);
    TEST_CHECK(actual_checker==biased_checker);

    //unexplored nodes return 0 because L has the same nodes as V

    L={0,1,2,3};
    V={0,1,2,3};
    biased_checker=0;
    actual_checker=unexplored_nodes(L,V);
    TEST_CHECK(actual_checker==biased_checker);

    L={0,1,2};
    V={0,1,2,3};
    actual_checker=unexplored_nodes(L,V);
    TEST_CHECK(actual_checker==biased_checker);

}

void test_addtoL(){
    set <int> L;
    set <int> neighbors;
    map <int,float> distances;
    int L_sizelist;

    L_sizelist=3;
    neighbors={1,2,3};
    distances={{1,float(7.65)},{2,float(4.5)},{3,float(8)}};
    addtoL(neighbors,L,distances,L_sizelist);

    set <int>::iterator lit=L.begin();
    TEST_CHECK(*lit==2);
        lit++;
        TEST_CHECK(*lit==1);
        lit++;
        TEST_CHECK(*lit==3);
    }


TEST_LIST{
    {"test_unexplored_nodes",test_unexplored_nodes},
    {"test_addtoL()",test_addtoL},
    {NULL, NULL}  // Terminate the test list


};