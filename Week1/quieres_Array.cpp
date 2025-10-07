#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) 
        cin >> arr[i];

    string s;
    cin >> s; // đọc dấu *

    cin.ignore(); // bỏ newline

    while (true) {
        string line;
        getline(cin, line);
        if (line == "***") 
            break;

        stringstream ss(line);//biến dòng string của line thành một luồng để đọc từng token.
        string cmd;
        ss >> cmd;//lấy từ đầu tiên trong dòng ra (ở đây là tên câu lệnh như find-max, sum, find-max-segment).

        if (cmd == "find-max") {
            cout << *max_element(arr.begin(), arr.end()) << "\n";
        }
        else if (cmd == "find-min") {
            cout << *min_element(arr.begin(), arr.end()) << "\n";
        }
        else if (cmd == "sum") {
            cout << accumulate(arr.begin(), arr.end(), 0) << "\n";
        }
        else if (cmd == "find-max-segment") {
            int i, j;
            ss >> i >> j;
            int mx = arr[i-1];
            for (int k = i-1; k < j; k++) {
                mx = max(mx, arr[k]);
            }
            cout << mx << "\n";
        }
    }
    return 0;
}


// Example
// Input
// 5
// 1 4 3 2 5
// *
// find-max
// find-min
// find-max-segment 1 3
// find-max-segment 2 5
// sum
// ***

// Output
// 5
// 1
// 4
// 5
// 15