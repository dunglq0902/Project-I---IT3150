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
            dfs(v); //Chạy đệ quy nếu chưa đi qua đỉnh v
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
        adj[u].push_back(v);    //Nhập vào các đỉnh kề v của u
        adj[v].push_back(u);
    }
    
    // Sắp xếp danh sách kề theo thứ tự từ điển
    for (int i = 1; i <= n; i++) {
        sort(adj[i].begin(), adj[i].end());
    }
    
    // Khởi tạo mảng visited
    memset(visited, false, sizeof(visited));    //memory set
    
    // Duyệt DFS từ đỉnh 1
    dfs(1);
    
    return 0;
}

// Bắt đầu từ 1: 1
// Từ 1 → 2 (nhỏ nhất trong [2,3])
// Từ 2 → 3 (nhỏ nhất trong [1,3,4,7], bỏ 1 vì đã thăm)
// Từ 3 → 5 (nhỏ nhất trong [1,2,5,7], bỏ 1,2 vì đã thăm)
// Từ 5 → 4 (nhỏ nhất trong [3,4,6,7], bỏ 3 vì đã thăm)
// Từ 4 → 6 (nhỏ nhất trong [2,5,6,7], bỏ 2,5 vì đã thăm)
// Từ 6 không đi tiếp được (các đỉnh kề đã thăm)
// Quay lại 4 → 7 (tiếp theo trong danh sách)