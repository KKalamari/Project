#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <unordered_set>

using namespace std;

// Function to convert a space-separated string of integers to a list of integers
list<int> stringToList(const string& input) {
    list<int> result;
    stringstream ss(input);
    string token;
    
    // Read tokens and convert them to integers
    while (ss >> token) {
        // Remove any unwanted characters and convert to int
        try {
            int number = stoi(token);  // Converts string to int
            result.push_back(number);
        } catch (invalid_argument&) {
            // Ignore if token is not a valid integer
        }
    }
    
    return result;
}

void comparing() {
    // Initial hardcoded list
    list<int> list1 = {97, 107, 121, 123, 124, 146, 149, 190, 224, 287, 292, 348, 370, 420,
     492, 598, 641, 696, 816, 882, 924, 942, 1038, 1045, 1064, 1156, 1254, 1272, 1292, 1295,
      1317, 1625, 1682, 1689, 1710, 1756, 1884, 1895, 1916, 1995, 2005, 2154, 2176, 2436, 2456, 
      2648, 2763, 2774, 2776, 2791, 2837, 2852, 2890, 2952, 3013, 3043, 3066, 3138, 3210, 3237,
       3449, 3515, 3530, 3543, 3553, 3615, 3625, 3687, 3752, 3814, 4002, 4009, 4050, 4058, 4064, 
       4094, 4096, 4263, 4293, 4320, 4321, 4527, 4938, 5231, 5307, 5375, 6139, 6630, 6837, 7245, 
       8731, 8887, 9211, 9541, 9576, 9701, 9734, 9758, 9806, 9814};

    // Input string for list2
    string input = " 2176 3752 882 4009 2837 190 816 1045 1884 224 3013 292 1272 5307 4938 1295 492 3625 1254 1292 1625 3553 1156 146 107 5231 1995 9541 3543 9758 9806 1064 9701 4064 2456 2763 3237 1317 3530 641 1710 8887 4263 1756 598 370 2776 121 4058 7245 1895 124 8731 696 4527 4050 2648 1682 1689 2436 2005 3210 4002 2774 924 6630 9814 3515 5375 287 1038 4096 4094 942 4321 123 3814 97 4293 420 9734 1916 9576 6837 2952 3138 2890 3066 2852 348 3043 9825 4125 106 1370 3056 2301 286 4241 3249";
    // Convert input string to list2
    list<int> list2 = stringToList(input);

    // Using a set for fast lookups
    unordered_set<int> set1(list1.begin(), list1.end());
    int count = 0;

    for (const auto& node2 : list2) {
        if (set1.find(node2) != set1.end()) {
            count++;
        }
    }

    // Print sizes of both lists
    cout << "Size of list1: " << list1.size() << endl;
    cout << "Size of list2: " << list2.size() << endl;
    cout << "The mutual elements are: " << count << endl;
}

int main() {
    comparing();
    return 0;
}
