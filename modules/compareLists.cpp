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

int  comparing() {
    // Initial hardcoded list
    list<int> list1 = {97, 107, 121, 123, 124, 146, 149, 190, 224, 287, 292, 348, 370, 420, 492, 598, 641, 696, 816, 882,
924, 942, 1038, 1045, 1064, 1156, 1254, 1272, 1292, 1295, 1317, 1625, 1682, 1689, 1710, 1756, 1884,
1895, 1916, 1995, 2005, 2154, 2176, 2436, 2456, 2648, 2763, 2774, 2776, 2791, 2837, 2852, 2890, 
2952, 3013, 3043, 3066, 3138, 3210, 3237, 3449, 3515, 3530, 3543, 3553, 3615, 3625, 3687, 3752, 
3814, 4002, 4009, 4050, 4058, 4064, 4094, 4096, 4263, 4293, 4320, 4321, 4527, 4938, 5231, 5307, 
5375, 6139, 6630, 6837, 7245, 8731, 8887, 9211, 9541, 9576, 9701, 9734, 9758, 9806, 9814};

    cout <<"the size of list is"<<list1.size()<<endl;;

    // Input string for list2
    list <int> list2 = {97,106,107,121,123,124,146,149,190,224,287,292,348,370,420,492,598,641,696,816,882,924,942,
    1038,1045,1064,1156,1254,1272,1292,1295,1317,1370,1625,1682,1689,1710,1756,1884,1895,1916,1995,2154,2176,2436,2456,2648,2763,
    2774,2776,2791,2837,2852,2952,3013,3043,3056,3066,3138,3210,3237,3449,3515,3530,3543,3553,3615,3625,3687,3752,4002,4009,4050,
    4064,4096,
    4125,4263,4293,4320,4321,4527,4938,5231,5307,5375,6139,6630,6837,7245,8731,8887,9211,9541,9576,9701,9734,9758,9806,9814,9825};

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
