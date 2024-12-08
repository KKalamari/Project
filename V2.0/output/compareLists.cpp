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
    list<int> list1 = {6544, 2251, 162, 9762, 1860, 3587, 4698, 5310, 5458, 5233, 7690, 3068, 6434, 5229, 1356, 4766, 4013, 5234, 304, 1528, 5298, 2752, 1718, 605, 4186, 8050, 9083, 1526, 4478, 5583, 5075, 83, 900, 435, 163, 7345, 8726, 4824, 7936, 9024, 2629, 1519, 4714, 6992, 2552, 4489, 783, 6158, 7527, 5207, 2837, 4088, 1705, 6643, 6470, 7036, 755, 260, 5021, 3857, 395, 6681, 1226, 7270, 469, 5905, 1467, 8673, 9563, 6323, 6454, 7391, 2276, 8889, 3732, 1130, 4463, 7657, 5295, 5895, 1310, 9693, 5498, 4427, 4574, 5293, 2760, 2436, 78, 9636, 7940, 116, 3606, 8181, 9787, 2361, 1051, 7709, 5864, 1761,
};

    cout <<"the size of list is"<<list1.size()<<endl;;

    // Input string for list2
    list <int> list2 = {6544, 2251, 162, 9762, 1860, 3587, 4698, 5458, 5233, 7690, 3068, 6434, 1356, 4766, 4013, 5234, 304, 1528, 5298, 2752, 1718, 605, 8050, 9083, 1526, 4478, 5583, 5075, 83, 900, 435, 163, 7345, 4824, 9024, 2629, 1519, 4714, 2552, 783, 6158, 2837, 4088, 1705, 6643, 6470, 7036, 755, 260, 5021, 3857, 395, 6681, 1226, 7270, 469, 5905, 1467, 8673, 9563, 6454, 7391, 2276, 3732, 1130, 4463, 7657, 5295, 1310, 9693, 5498, 4427, 2760, 2436, 78, 9636, 7940, 116, 3606, 8181, 9787, 2361, 1051, 7709, 5864, 1761, 6097, 391, 3251, 9463, 1354, 864, 8167, 7806, 3600, 8011, 1347, 983, 5065, 6956};

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
