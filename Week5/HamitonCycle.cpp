#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

vector<int> adj[20];
bool visited[20];
int n, m;

// Hàm kiểm tra xem có chu trình Hamilton bắt đầu từ đỉnh start hay không
bool hamiltonianCycle(int start, int current, int count) {
    // Nếu đã đi qua tất cả các đỉnh
    if (count == n) {
        // Kiểm tra xem đỉnh hiện tại có kề với đỉnh xuất phát không
        for (int neighbor : adj[current]) {
            if (neighbor == start) {
                return true;
            }
        }
        return false;
    }
    
    // Duyệt qua tất cả các đỉnh kề
    for (int neighbor : adj[current]) {
        if (!visited[neighbor]) {
            visited[neighbor] = true;
            if (hamiltonianCycle(start, neighbor, count + 1)) {
                return true;
            }
            visited[neighbor] = false;
        }
    }
    return false;
}

// Hàm kiểm tra xem đồ thị có phải là Hamilton hay không
bool isHamiltonian() {
    for (int start = 1; start <= n; start++) {// Kiểm tra tất cả các đỉnh làm điểm bắt đầu
        memset(visited, false, sizeof(visited));    //Reset mảng visited cho mỗi lần thử,tức là đánh dấu toàn bộ là false
        visited[start] = true;
        if (hamiltonianCycle(start, start, 1)) {
            return true;
        }
    }
    return false;
}

int main() {
    int T;
    cin >> T;
    
    while (T--) {
        cin >> n >> m;
        
        // Reset đồ thị
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
        }
        
        // Đọc các cạnh
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);    //Ví dụ:adj[1] = [2,3,4] Đây là danh sách kề
            adj[v].push_back(u);    //Làm ngược lại tạo ra cạnh có đường đi 2 chiều
        }
        
        // Kiểm tra và in kết quả
        if (isHamiltonian()) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
    }
    
    return 0;
}