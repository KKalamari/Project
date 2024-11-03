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
    list <int> list2 = {97,106,107,121,123,124,145,146,149,174,190,217,224,286,287,292,348,370,396,402,420,421,492,579,598,613,641,
    662,696,816,882,924,942,953,1038,1045,1064,1095,1156,1250,1254,1272,1292,1295,1317,1323,1454,1468,1518,1543,1578,1619,1625,1682,
    1689,1756,1848,1895,1916,1995,2002,2005,2039,2176,2301,2306,2388,2436,2648,2791,2837,2852,2908,3043,
    3066,3138,3449,3515,3553,3591,3625,3947,4009,4063,4163,4241,4293,4447,5231,5307,6630,6837,9211,9541,9576,9594,9605,9701,9758,
    9922};

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
