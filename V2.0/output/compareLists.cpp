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
    list<int> list1 = {2504, 5234, 7081, 7879, 4013, 5910, 7061, 4911, 9718, 8875, 7483, 3536, 1647, 1226, 8041, 3580, 4260, 359, 6494, 7709, 9389, 6454, 7611, 1634, 3176, 9829, 9687, 5592, 5073, 6151, 5543, 6404, 7530, 4270, 8181, 9204, 8904, 2276, 2548, 2144, 2921, 5519, 3655, 3581, 6463, 9914, 293, 8640, 1085, 7074, 6434, 2422, 6985, 9357, 3972, 4284, 7732, 9567, 4557, 706, 9529, 5035, 2399, 4593, 4399, 8742, 1125, 9633, 1917, 9854, 9867, 3521, 8224, 2327, 4032, 4961, 9507, 996, 1359, 146, 408, 5654, 7190, 5586, 5630, 5594, 8306, 6732, 6342, 2621, 4434, 9953, 9334, 6992, 4698, 6308, 6873, 9036, 8938, 8197
};

    cout <<"the size of list is"<<list1.size()<<endl;;

    // Input string for list2
    list <int> list2 = {2504, 5234, 7081, 7879, 4013, 5910, 7061, 4911, 9718, 8875, 7483, 3536, 1647, 1226, 8041, 3580, 4260, 359, 6494, 7709, 9389, 6454, 7611, 1634, 3176, 9829, 9687, 5592, 5073, 6151, 5543, 6404, 7530, 4270, 8181, 9204, 8904, 2276, 2548, 2144, 2921, 5519, 3655, 3581, 6463, 9914, 293, 8640, 1085, 7074, 6434, 2422, 6985, 9357, 3972, 4284, 7732, 9567, 4557, 706, 9529, 5035, 2399, 4593, 4399, 8742, 1125, 9633, 1917, 9854, 9867, 3521, 8224, 2327, 4032, 4961, 9507, 996, 1359, 146, 408, 5654, 7190, 5586, 5630, 5594, 8306, 6732, 6342, 2621, 4434, 9953, 9334, 6992, 4698, 6308, 6873, 9036, 8938, 8197 };

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
