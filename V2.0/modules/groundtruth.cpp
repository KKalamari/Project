
#include "groundtruth.h"
#include <algorithm>
#include<queue>
#include <vector>

void groundtruth (vector<vector<float>>&DataNodes,vector<vector<float>>&queries, vector<vector<double>> &datamatrix,vector<vector<double>>&querymatrix,vector<vector<int>>&ground){
    int query_size = queries.size();
    cout<<" the queries size is"<<query_size<<endl;
    ground.resize(query_size); //initialing vector ground
    int data_size = DataNodes.size();
    // vector <vector<int>> neighbors(query_size);
    

    for(int i=0;i<query_size;i++){
  
        int k=0;        
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> candidates_neighbors;
            for(int j=0;j<data_size;j++){
                
                if(queries[i][1]== DataNodes[j][0] || queries[i][1]==-1){ //if they have the same filter or it's unfiltered.
                    double distance = querymatrix[j][i];
                    int node = j;
                    candidates_neighbors.emplace( make_pair(distance,node));
                }
                
            }
            

        int count = min(100,int(candidates_neighbors.size()));
        for(int k =0;k<count;k++){
            pair<double,int> node = candidates_neighbors.top(); //loading the 1st element
            int inserting_neighbor = node.second;
            // neighbors[i].push_back(inserting_neighbor); 
            
            ground[i].push_back(inserting_neighbor); //pushing the nodes from minimum to maximum order into ground vector
            candidates_neighbors.pop(); //removing the 1st element now that it's used.
        }
        
    }

    // Write results to a text file
    ofstream outfile("groundtruth.txt"); // Open a file named "neighbors.txt"
    if (outfile.is_open()) {
        for (int i =0; i <query_size; i++) {
            outfile << "Nearest neighbors for query " << i  <<" with FQ =" <<queries[i][1]<< " and query type  "<<queries[i][0]<< " :" ;
            for (const auto &node: ground[i]) {
                outfile << node << ", ";
            }
            outfile << endl;
        }
        outfile.close(); // Close the file
        cout << "results written succesfully!" << endl;
    } else {
        cerr << "Error writing in the txt file." << endl;
    }
}

