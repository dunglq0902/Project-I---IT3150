#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, M;
    cin >> n >> M;
    unordered_set<int> seen;
    long long count = 0;

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        if (seen.find(M - x) != seen.end()) {
            count++;
        }
        seen.insert(x);
    }

    cout << count;
    return 0;
}
