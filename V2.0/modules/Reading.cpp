#include <iostream>
#include<vector>
#include <fstream>
#include <string>
#include <numeric>
#include <set>
#include "Reading.h"
using namespace std;
set<float> ReadBin(const string &file_path,
                   int num_dimensions,
                   std::vector<std::vector<float>> &data) {
    set<float> category_attributes;
    std::cout << "Reading Data: " << file_path << std::endl;
    std::ifstream ifs;
    ifs.open(file_path, std::ios::binary);
    int N;  // num of points
    ifs.read((char *)&N, sizeof(int)); // reading the first element of file (size)
    
    // Cap N to 100,000 to limit data size
    if (N > 11000) {
        std::cout << "Limiting the number of points to 100,000 (from " << N << ")" << std::endl;
        N = 11000;
    }
    
    data.resize(N);
    std::cout << "# of points: " << N << std::endl;
    std::vector<float> buff(num_dimensions);
    int counter = 0;

    while (counter < N && ifs.read((char *)buff.data(), num_dimensions * sizeof(float))) {
        std::vector<float> row(num_dimensions);
        for (int d = 0; d < num_dimensions; d++) {
            row[d] = static_cast<float>(buff[d]);
        }
        data[counter++] = std::move(row);

        // Save each unique category for later (medoid)
        category_attributes.insert(data[counter - 1][0]);
    }

    ifs.close();
    std::cout << "Finish Reading Data" << std::endl;
    return category_attributes;
}


            




            
                        