#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
//Bài toán: Tìm khoảng cách ngắn nhất giữa mọi cặp đỉnh trong đồ thị có hướng

using namespace std;

const int INF = 1e9; // Giá trị vô cùng (thay cho -1 khi chưa có đường đi)

int main() {
    int n, m;
    //n: số đỉnh (nodes) - các đỉnh được đánh số từ 1 đến n
    //m: số cạnh (edges) - số đường đi có hướng giữa các đỉnh
    cin >> n >> m;
    
    // Khởi tạo ma trận khoảng cách
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    //ma trận 2 chiều với n+1 hàng và n+1 cột với từng giá trị là INF
    
    // Khoảng cách từ 1 đỉnh tới chính nó là 0
    for (int i = 1; i <= n; i++) {
        dist[i][i] = 0;
    }
    
    // Đọc dữ liệu đầu vào
    for (int i = 0; i < m; i++) {
        int u, v, w;    //u: đỉnh bắt đầu, v: đỉnh kết thúc, w: trọng số (độ dài) của cung từ u đến v
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w); // Lấy trọng số nhỏ nhất nếu có nhiều cạnh
    }
    
    // Thuật toán Floyd-Warshall
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    // In kết quả
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] == INF) {
                cout << -1 << " ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}