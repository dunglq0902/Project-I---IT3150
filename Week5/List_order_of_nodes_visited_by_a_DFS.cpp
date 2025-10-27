#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 100005;

vector<int> adj[MAXN];
bool visited[MAXN];

void dfs(int u) {
    cout << u << " ";
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);   //Tắt đồng bộ hóa giữa C và C++
    cin.tie(NULL);  //Ngắt liên kết cin với cout để tăng tốc độ nhập xuất
    
    int n, m;
    cin >> n >> m;
    
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
    
    // Khởi tạo mảng visited
    memset(visited, false, sizeof(visited));
    
    // Duyệt DFS từ đỉnh 1
    dfs(1);
    
    return 0;
}