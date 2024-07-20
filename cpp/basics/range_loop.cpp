#include <iostream>
#include <vector>
using std::cout;
using std::vector;

int main() {
    // Add your code here.
    vector<vector<int>> b {{1, 2},
                           {3, 4},
                           {5, 6}};

    for (vector i: b) {
        for (int j: i) {
            // cout << i << ", " << j << "\n";
            cout << j << "\n";
        }
    }
    
}