#include <bits/stdc++.h>
#include <sstream>
#include <string>
using namespace std;

int main()
{
    int count = 0;
    string line;

    while(getline(cin, line))
    {
        stringstream ss(line);
        string token;
        while(ss >> token){
            count++;
        }
    }
    cout<<count<<endl;
    return 0;
}

// Input
// Hanoi University Of Science and Technology
// School of Information and Communication Technology


// Output
// 12