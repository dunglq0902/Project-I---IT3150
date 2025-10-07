#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 1000;

// Bảng lưu trữ kết quả: comb[i][j] = C(i, j)
vector<vector<int>> comb(MAX + 1, vector<int>(MAX + 1, 0));

void precomputeCombinations() {    
    // Bước 1: Khởi tạo các trường hợp cơ sở
    for (int i = 0; i <= MAX; i++) 
    {
        comb[i][0] = comb[i][i] = 1;// C(i,0) = 1 và C(i,i) = 1
        // Bước 2: Tính các trường hợp còn lại
        for (int j = 1; j < i; j++) 
        {// Áp dụng công thức Pascal với modulo
            comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % MOD;
        }
    }
}

int combination(int n, int k) 
{
    if (k < 0 || k > n) 
        return 0;
    return comb[n][k];
}

int main() {
    // Tính trước tất cả tổ hợp từ 0 đến MAX
    precomputeCombinations();
    
    int n, k;
    cin >> k >> n;
    int result = combination(n, k);
    cout <<result << endl;
    
    return 0;
}
// Description
// Given two positive integers k and n. Compute C(k,n) which is the number of ways to select k objects from a given set of n objects.
// Input
// Line 1: two positive integers k and n (1 <= k,n <= 999)
// Output
// Write te value C(k,n) modulo 10
// 9
// +7.
// Example
// Input
// 3  5
// Output
// 10