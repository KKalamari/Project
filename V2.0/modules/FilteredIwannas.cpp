// FilteredGreedySearch function 
set<int> FilteredGreedySearch(vector<Vertex> graph, unordered_map<float, int> s, int xq, float query_label, int K, int L, set<int>& k_closest, vector<vector<double>>& distanceMap, set<float> label_set, set<int> medoids) {
    // Set to store the nearest neighbors for the query
    unordered_set<int> L_call;
    // Priority queue with pairs <euclidean_distance, node_id>
    priority_queue<pair<double, int>> L_call_euclidean = {};
    // Set to store the visited nodes
    set<int> V;
    // Set to store the neighbors that are not exist in the visited set (L_calligraph - V)
    unordered_set<int> L_V;

    // If the query has no label
    if(query_label == -1.0) {
        // For all the labels
        for(const auto& lab : label_set) {
            float s_lab = s[lab];
            
            // Insert in the sets the medoid for the label
            L_call.insert(s_lab);
            L_call_euclidean.push(make_pair(distanceMap[xq][s_lab], s_lab));
            L_V.insert(s_lab);
        }
    }
    // If the query has a label
    else {
        float s_query_label = s[query_label];

        // Insert in the sets tha label's medoid
        L_call.insert(s_query_label);
        L_call_euclidean.push(make_pair(distanceMap[xq][s_query_label], s_query_label));
        L_V.insert(s_query_label);
    }

    while(L_V.empty() == false) {
        
        double min_distance = numeric_limits<double>::max();
        int p_star = -1;

        // For every node that exists in L set and not exists in V
        for(const int& node : L_V) {
            // Calculate the distance between current node and the query node
            double distance = distanceMap[xq][node];

            // Update the minimum distance and the node number
            if(distance < min_distance) {
                min_distance = distance;
                p_star = node;
            }
        }

        // Insert the minimum node in the visisted set 
        V.insert(p_star);

        // A set to store the p_star neighbors 
        set<int> Nf_out = {};

        // For every p_star neighbor
        for(const int& neighbor : graph[p_star].neighbors) {
            // If the neighbor has the same label with the query 
            // or if the query has no lebel and there isn't in the visited set
            if(((graph[neighbor].label == query_label) || (query_label == -1)) && (V.find(neighbor) == V.end()))
                Nf_out.insert(neighbor);
        }
        
        // For every node in the p_star's neighbors
        for(const int& element : Nf_out) {
            // Insert the nodes in the sets
            L_call.insert(element);
            L_call_euclidean.push(make_pair(distanceMap[xq][element], element));
        }
        // While the size is bigger than L number
        while(L_call.size() > L) {
            // Set to store the poped elements from the 'L_call_sorted_euclidean'
            set<pair<double, int>> poped_elements;
            int flag = 0;
            auto lastElement = L_call_euclidean.top();

            // While the element with the max euclidean distance is a medoid and it isn't visited
            do
            {
                flag = 0;
                // Get the last element from 'L_call_euclidean'
                lastElement = L_call_euclidean.top();

                // If the last element is a medoid and it isn't visited
                if((medoids.find(lastElement.second) != medoids.end()) && (V.find(lastElement.second) == V.end())) {
                    // Delete it from the queue
                    L_call_euclidean.pop();
                    // Put it in the poped set
                    poped_elements.insert(make_pair(lastElement.first, lastElement.second));
                    flag = 1;
                }
            } while(flag == 1);

            L_call.erase(lastElement.second);
            L_call_euclidean.pop();

            // Insert back in the 'L_call_euclidean' all the poped elements
            for(auto popped : poped_elements)
                L_call_euclidean.push(popped);
        }

        // Clean the "L_calligraph - V" set
        L_V.clear();

        // Add int the "L_calligraph - V" set the nodes that exists in L set and don't exists in V set
        for(const int& node : L_call) {
            if(V.find(node) == V.end())
                L_V.insert(node);
        }  
    }

    if(K > 0) {
        // While the size is bigger than the K
        while(L_call.size() > K) {
            // Get the last element from 'L_call_euclidean'
            auto lastElement = L_call_euclidean.top();

            // Delete it from the set and the queue
            L_call.erase(lastElement.second);
            L_call_euclidean.pop();  
        }

        // Add in the K closest neighbors set the k nodes with the minimum distance from the L set
        for(const int& node : L_call)
            k_closest.insert(node);
    }
    
    // Return the visited nodes set
    return V;
}