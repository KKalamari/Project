#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
vector<vector<int>> reading_groundtruth() {
    vector <vector<int>>ground;
    ifstream file("../output/groundtruth.txt");      

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
    }

    string line;
    while (std::getline(file, line)) {
        // Find the position of the colon
        size_t colonPos = line.find(':');
        int num;
        if (colonPos != std::string::npos) {
            std::string numbersPart = line.substr(colonPos + 1);
            std::istringstream ss(numbersPart);
            std::vector<int> neighbors;
            

            // Extract numbers separated by commas
            while (ss >> num) {
                neighbors.push_back(num);
                if (ss.peek() == ',') ss.ignore();
            }

            // Add to the main vector
            ground.push_back(neighbors);
        }
    }

    file.close();

   

    return ground;
}
