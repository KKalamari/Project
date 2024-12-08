#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include "medoid.h"
#include "acutest.h"

using namespace std;
// Helper function to create a sample dataset
std::vector<std::vector<float>> createTestDataset() {
    // Create a sample dataset where each vector represents a point with attributes
    return {
        {1, 0}, {2, 1}, {1, 2}, {3, 3}, {4, 4}, {1, 1}, {3, 1}, {4, 2}
    };
}

//medoid is built randomly so the test cases are focused over edge cases with threshold
void MedoidTest() {
    set<float>categories={1,2,3,4};
    std::vector<std::vector<float>> dataset = createTestDataset();
    int r = 3; 
    map<float, int> result = FindMedoid(dataset, r,categories);
    TEST_CHECK(!result.empty()); 
    TEST_MSG("Result should not be empty");
    
    //test 2,checking an edge case with an empty dataset
    std::vector<std::vector<float>> emptyDataset;
    set<float>filters;
    result = FindMedoid(emptyDataset, r,filters);
    TEST_CHECK(result.empty());
    TEST_MSG("the size should be empty!!");
    
    //test3, checking an edge case with r larger than dataset size
    r = 10;
    result = FindMedoid(dataset, r,categories);
    TEST_CHECK(!result.empty());
    TEST_MSG("Pruning does not happen correctly when r is bigger than the actual dataset");
    for (const auto& entry : result) {
        std::cout << "Filter " << entry.first << " maps to start node " << entry.second << std::endl;
    }
    
    // a singleton daaset case
    std::vector<std::vector<float>> singlePointDataset = {{5, 5}};
    filters={5};
    result = FindMedoid(singlePointDataset, r, filters);
    TEST_CHECK(result.size() == 1);
    TEST_MSG("The size should always be 1 in a single point dataset");

    
   
}

TEST_LIST{
    {"MedoidTest",MedoidTest},
    {"NULL",NULL}
};
