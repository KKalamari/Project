#include "for_binary.h"


void save_graph_to_binary_set(const std::map<int, std::set<int>>& graph, const std::string& filename)
{
    const std::string folder = "./../graphs/";

    std::string full_path = folder + filename;

    std::ofstream outfile(full_path, std::ios::binary);
    
    if (!outfile)
    {
        std::cerr << "Error opening file for writing: " << full_path << std::endl;
        return;
    }
    
    for (const auto& pair : graph) 
    {
        int node_id = pair.first;  
        const std::set<int>& neighbors = pair.second;  
        
        outfile.write(reinterpret_cast<const char*>(&node_id), sizeof(node_id));
        
        int num_neighbors = neighbors.size();
        outfile.write(reinterpret_cast<const char*>(&num_neighbors), sizeof(num_neighbors));
        
        for (int neighbor : neighbors)
        {
            outfile.write(reinterpret_cast<const char*>(&neighbor), sizeof(neighbor));
        }
    }
    
    outfile.close();
}


bool load_graph_from_binary(const std::string& filename, std::map<int, std::set<int>>& graph)
{
    
    const std::string folder = "./../graphs/";

    std::string full_path = folder + filename;

    std::ifstream infile(full_path, std::ios::binary);
    
    if (!infile)
    {
        std::cerr << "Error opening file for reading: " << full_path << std::endl;
        return false;
    }

    while (infile)
    {
        int node_id;
        int num_neighbors;
        
        infile.read(reinterpret_cast<char*>(&node_id), sizeof(node_id));
        infile.read(reinterpret_cast<char*>(&num_neighbors), sizeof(num_neighbors));

        if (infile.eof()) break;

        std::set<int> neighbors;
        for (int i = 0; i < num_neighbors; ++i)
        {
            int neighbor;
            infile.read(reinterpret_cast<char*>(&neighbor), sizeof(neighbor));
            neighbors.insert(neighbor);
        }

        graph[node_id] = neighbors;
    }

    infile.close();
    return true;
}
