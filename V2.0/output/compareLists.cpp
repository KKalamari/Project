#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <unordered_set>

using namespace std;

// Function to convert a space-separated string of integers to a list of integers
// list<int> stringToList(const string& input) {
//     list<int> result;
//     stringstream ss(input);
//     string token;
    
//     // Read tokens and convert them to integers
//     while (ss >> token) {
//         // Remove any unwanted characters and convert to int
//         try {
//             int number = stoi(token);  // Converts string to int
//             result.push_back(number);
//         } catch (invalid_argument&) {
//             // Ignore if token is not a valid integer
//         }
//     }
    
//     return result;
// }

int  comparing() {
    // Initial hardcoded list
    list<int> list1 = {4235, 9478, 6523, 635, 2161, 1226, 4865, 2251, 4560, 6693, 2709, 305, 6414, 1285, 9242, 6342, 2601, 9521, 6516, 2274, 7400, 3122, 2803, 1471, 5965, 264, 1892, 9389, 9743, 627, 3251, 245, 8093, 5181, 6688, 276, 4552, 9427, 9548, 5471, 1566, 9357, 8582, 2003, 3857, 3341, 6143, 1803, 8778, 2972, 3836, 6096, 6199, 9838, 201, 7493, 8182, 698, 5549, 8139, 2805, 4266, 2642, 9024, 9416, 4925, 8522, 7260, 5176, 2208, 2512, 9498, 5275, 1463, 768, 4345, 2068, 2658, 8273, 8682, 1088, 7752, 580, 6337, 473, 6316, 7421, 8418, 899, 1589, 6491, 1577, 6169, 3267, 8641, 4305, 5685, 4667, 5486, 531
};

    cout <<"the size of list is"<<list1.size()<<endl;;

    // Input string for list2
    list <int> list2 = {4235, 9478, 6523, 635, 2161, 1226, 4865, 2251, 4560, 6693, 2709, 305, 6414, 1285, 9242, 6342, 2601, 9521, 6516, 2274, 7400, 3122, 2803, 1471, 5965, 264, 1892, 9389, 9743, 627, 3251, 245, 8093, 5181, 6688, 276, 4552, 9427, 9548, 5471, 1566, 9357, 8582, 2003, 3857, 3341, 6143, 1803, 8778, 2972, 3836, 6096, 6199, 9838, 201, 7493, 8182, 698, 5549, 8139, 2805, 4266, 2642, 9024, 9416, 4925, 8522, 7260, 5176, 2208, 2512, 9498, 5275, 1463, 768, 4345, 2068, 2658, 8273, 8682, 1088, 7752, 580, 6337, 473, 6316, 7421, 8418, 899, 1589, 1939, 6491, 1577, 6169, 3267, 8641, 4305, 5685, 4667, 5486, };

    cout <<"the size of list 2 is"<<list2.size()<<endl;

    int common=0;
    for(list <int> ::iterator nodes1 =list1.begin();nodes1!=list1.end();nodes1++){
        for(list <int> :: iterator nodes2 = list2.begin(); nodes2!=list2.end();nodes2++){
            if(*nodes1==*nodes2){
                common++;
                break;
            }
        }
    }
    return common;

}

int main() {
    int common =comparing();
    cout <<"common elements are:"<<common<<endl;
}
