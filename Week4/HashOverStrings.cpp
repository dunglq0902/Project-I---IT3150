#include <iostream>
#include <string>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        
        long long hash = 0;
        long long power = 1;
        
        //Tính chất của modulo
        //(a + b) mod m = [(a mod m) + (b mod m)] mod m
        //(a × b) mod m = [(a mod m) × (b mod m)] mod m

        // Tính hash từ phải sang trái
        for (int j = s.length() - 1; j >= 0; j--) {
            hash = (hash + (s[j] * power) % m) % m;
            power = (power * 256) % m;
        }
        
        cout << hash << endl;
    }
    
    return 0;
}