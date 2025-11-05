#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> adj(n + 1); //Tạo Danh sách kề dùng vector of vector
    
    // Đọc các cạnh
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // Sắp xếp danh sách kề theo thứ tự từ điển
    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
    }
    
    vector<bool> visited(n + 1, false);
    vector<int> result;
    
    // Duyệt qua tất cả các đỉnh từ 1 đến n
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            queue<int> q;
            visited[i] = true;
            q.push(i);
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                result.push_back(u);
                
                // Duyệt các đỉnh kề theo thứ tự từ điển
                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    }
    
    // In kết quả
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << " ";
    }
    
    return 0;
}