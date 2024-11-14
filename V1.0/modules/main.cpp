#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <chrono>
#include <fstream>
#include <map>
#include <sstream>
#include "reading.h"
#include "graph_creation.h"
#include "greedysearch.h"
#include "euclidean_distance.h"
#include "vamana.h"
#include "json.hpp"

//define the json from the nlohmann library
using json = nlohmann::json;

using namespace std;
using namespace chrono;

// Function to read configuration from a file
// Function to load configuration from a JSON file
json readConfig(const string& config_filename) {
    json config_data;

    // Open config.json file
    ifstream config_file(config_filename);
    
    if(!config_file.is_open())
        throw runtime_error("Unable to open config file.");

    // Read JSON data
    config_file >> config_data;

    // Close the file
    config_file.close();

    return config_data;
}
int main(int argc, char** argv) {
    auto start = high_resolution_clock::now();

json config_data;
    try {
        config_data = readConfig("../../.vscode/config.json"); // replace with actual config filename if different
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    // Retrieve values from the config using the exact names
    string filename = config_data.value("filename", "default_base.fvecs");
    string filename2 = config_data.value("filename2", "default_query.fvecs");
    string filename3 = config_data.value("filename3", "default_groundtruth.ivecs");
    int k_neigh = config_data.value("k_neigh", 0);
    int R = config_data.value("R", 0);
    double a = config_data.value("a", 0.0);
    int L_sizelist = config_data.value("L_sizelist", 0);

    // Use values as needed
    cout << "filename: " << filename << endl;
    cout << "filename2: " << filename2 << endl;
    cout << "filename3: " << filename3 << endl;
    cout << "k_neigh: " << k_neigh << endl;
    cout << "R: " << R << endl;
    cout << "a: " << a << endl;
    cout << "L_sizelist: " << L_sizelist << endl;

    vector<vector<float>> vec = reading_fvecs(filename.c_str(), 1, 10000);
    vector<vector<float>> queries = reading_fvecs(filename2.c_str(), 1, 100);

    int vector_number = int(vec.size());
    int query_number = int(queries.size());

    vector<vector<double>> vecmatrix(vector_number, vector<double>(vector_number));
    vector<vector<double>> querymatrix(vector_number, vector<double>(query_number));

    euclidean_distance_of_database(vec, vecmatrix);
    euclidean_distance_of_queries(vec, queries, querymatrix);

    int medoid_node;
    map<int, list<int>> graph = vamana_index_algorithm(vec, R, medoid_node, L_sizelist, a, vecmatrix);
    int s = medoid_node;
    map<int, double> distances;
    vector<vector<int>> ground = reading_ivecs(filename3.c_str(), 1, 100);

    int k = 0;
    for (int i = 0; i < 100; i++) {
        vector<int> comp = ground[i];
        pair<set<int>, set<int>> L = greedysearch(graph, s, i, k_neigh, L_sizelist, querymatrix);
        set<int> setV = L.first;
        int count = 0;
        for (const int& value : comp) {
            if (setV.count(value) > 0)
                count++;
        }
        if (count >= 90)
            k++;
        cout << count << endl;
    }
    cout << k << endl;

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<minutes>(end - start);
    cout << "Execution time: " << duration.count() << " minutes" << endl;
}
