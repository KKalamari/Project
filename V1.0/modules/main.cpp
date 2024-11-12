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

using namespace std;
using namespace chrono;

// Function to read configuration from a file
void readConfig(const string& config_filename, string& filename, string& filename2, string& filename3,
                int& k_neigh, int& R, double& a, int& L_sizelist) {
    ifstream config_file(config_filename);
    if (!config_file.is_open()) {
        cerr << "Could not open config file: " << config_filename << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    while (getline(config_file, line)) {
        istringstream line_stream(line);
        string key;
        if (line_stream >> key) {
            if (key == "filename")
                line_stream >> filename;
            else if (key == "filename2")
                line_stream >> filename2;
            else if (key == "filename3")
                line_stream >> filename3;
            else if (key == "k_neigh")
                line_stream >> k_neigh;
            else if (key == "R")
                line_stream >> R;
            else if (key == "a")
                line_stream >> a;
            else if (key == "L_sizelist")
                line_stream >> L_sizelist;
        }
    }
}

int main(int argc, char** argv) {
    auto start = high_resolution_clock::now();

    // Default values
    string filename = "siftsmall_base.fvecs";
    string filename2 = "siftsmall_query.fvecs";
    string filename3 = "siftsmall_groundtruth.ivecs";
    int k_neigh = 100;
    int R = 16;
    double a = 1.1;
    int L_sizelist = 150;

    // Check for a config file provided as an argument, or use a default name
    string config_filename = (argc > 1) ? argv[1] : "config.txt";
    readConfig(config_filename, filename, filename2, filename3, k_neigh, R, a, L_sizelist);

    cout << "Using configuration:" << endl;
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
