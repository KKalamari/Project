
#include "groundtruth.h"
#include <algorithm>

void groundtruth (vector<vector<float>>&DataNodes,vector<vector<float>>&queries, vector<vector<double>> &datamatrix,vector<vector<double>>&querymatrix,vector<vector<int>>&ground){
    int query_size = queries.size();
    cout<<" the queries size is"<<query_size<<endl;
    ground.resize(query_size);
    int data_size = DataNodes.size();
    vector <vector<int>> neighbors(query_size);
    

    for(int i=0;i<query_size;i++){
  
        int k=0;        
        vector<pair<double,int>> candidates_neighbors;

            for(int j=0;j<data_size;j++){
                
                if(queries[i][1]== DataNodes[j][0] || queries[i][1]==-1){
                    double distance = querymatrix[j][i];
                    int node = j;
                    candidates_neighbors.push_back( make_pair(distance,node));
                    if(k==100)   
                        break;

                }
            }
            
        sort(candidates_neighbors.begin(),candidates_neighbors.end());

        int count = min(100,int(candidates_neighbors.size()));
        for(int k =0;k<count;k++){
            neighbors[i].push_back(candidates_neighbors[k].second);
            ground[i].push_back(candidates_neighbors[k].second);
        }
        
    }

    // Write results to a text file
    ofstream outfile("groundtruth.txt"); // Open a file named "neighbors.txt"
    if (outfile.is_open()) {
        for (int i =0; i <query_size; i++) {
            outfile << "Nearest neighbors for query " << i  <<" with FQ =" <<queries[i][1]<< " and query type  "<<queries[i][0]<< " :" ;
            for (const auto &node: neighbors[i]) {
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

