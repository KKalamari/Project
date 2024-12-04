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
    list<int> list1 = {373, 4748, 7843 ,7725 ,9421, 3811 ,5115 ,1078, 1271, 1450, 6326, 1798, 2399, 674, 9378, 1468 ,1336, 5167, 8985, 3686, 5911, 9949, 7239, 1428, 3088, 4270, 2073 ,8696, 4852, 3375, 7038, 5875, 6783, 9747, 1000, 8976, 3645 ,3445, 5969, 8264, 9300, 6347, 8042, 3562 ,2838 ,8958 ,9525 ,7307, 4446 ,5940 ,5758, 4830 ,537 ,1518, 7071 ,4432 ,8829, 3180, 8596, 1543 ,119 ,552 ,1962, 5098, 6406, 8707, 1274, 80 ,7808, 2497 ,4859, 1364, 5065, 8018, 2788, 3954, 6926, 4357, 4116, 7477, 2207, 6087, 4095, 5543, 2373 ,4600, 2812, 2654, 9854, 1886, 2813, 9400, 5741 ,7065, 4250 ,4104, 7955, 1526, 20 ,1544
};

    cout <<"the size of list is"<<list1.size()<<endl;;

    // Input string for list2
    list <int> list2 = {373, 4748, 7843, 7725, 9421, 3811, 5115, 1078, 1271, 1450, 6326, 1798, 2399, 674, 9378, 1468, 1336, 5167, 8985, 3686, 5911, 9949, 7239, 1428, 3088, 4270, 2073, 8696, 4852, 3375, 7038, 5875, 6783, 9747, 1000, 8976, 3645, 3445, 5969, 8264, 9300, 6347, 8042, 3562, 2838, 8958, 9525, 7307, 4446, 5940, 5758, 4830, 537, 1518, 7071, 4432, 8829, 3180, 8596, 1543, 119, 552, 1962, 5098, 6406, 8707, 1274, 80, 7808, 2497, 4859, 1364, 5065, 8018, 2788, 3954, 6926, 4357, 4116, 7477, 2207, 6087, 4095, 5543, 2373, 4600, 2812, 2654, 9854, 1886, 2813, 9400, 5741, 7065, 4250, 4104, 7955, 1526, 20, 1544};

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
