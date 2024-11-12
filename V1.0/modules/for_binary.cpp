#include "for_binary.h"

void save_graph_to_binary(const map<int, list<int>>& graph, const string& filename)
{
    ofstream outfile(filename, ios::binary);
    
    if (!outfile)
    {
        cerr << "Error opening file for writing.\n";
        return;
    }
    
    //write each node and its neighbors to the binary file
    for (const auto& [node, neighbors] : graph)
    {
        int node_id = node;
        int num_neighbors = neighbors.size();
        
        //write node ID and neighbor count
        outfile.write(reinterpret_cast<const char*>(&node_id), sizeof(node_id));
        outfile.write(reinterpret_cast<const char*>(&num_neighbors), sizeof(num_neighbors));
        
        //write each neighbor
        for (int neighbor : neighbors)
        {
            outfile.write(reinterpret_cast<const char*>(&neighbor), sizeof(neighbor));
        }
    }
    
    outfile.close();
}


map<int, list<int>> load_graph_from_binary(const string& filename)
{
    map<int, list<int>> graph;
    ifstream infile(filename, ios::binary);
    
    if (!infile)
    {
        cerr << "Error opening file for reading.\n";
        return graph;
    }
    
    while (infile.peek() != EOF)
    {  //while there's data in the file
        int node_id, num_neighbors;
        
        //read node ID and neighbor count
        infile.read(reinterpret_cast<char*>(&node_id), sizeof(node_id));
        infile.read(reinterpret_cast<char*>(&num_neighbors), sizeof(num_neighbors));
        
        list<int> neighbors;
        for (int i = 0; i < num_neighbors; ++i)
        {
            int neighbor;
            infile.read(reinterpret_cast<char*>(&neighbor), sizeof(neighbor));
            neighbors.push_back(neighbor);
        }
        
        graph[node_id] = neighbors;
    }
    
    infile.close();
    return graph;
}
