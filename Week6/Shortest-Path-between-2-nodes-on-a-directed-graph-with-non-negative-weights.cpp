#include <iostream>
#include <vector>
#include <queue>
#include <climits>  // Để sử dụng LLONG_MAX

using namespace std;

int main() {
    // Tối ưu hóa tốc độ nhập xuất
    ios_base::sync_with_stdio(false);  // Tắt đồng bộ với stdio để cin/cout chạy nhanh hơn
    cin.tie(NULL);                     // Bỏ liên kết giữa cin và cout
    
    // Bước 1: Đọc số đỉnh và số cung của đồ thị
    int n, m;
    cin >> n >> m;  // n = số đỉnh, m = số cung
    
    // Bước 2: Khởi tạo danh sách kề để biểu diễn đồ thị
    // graph[u] sẽ chứa danh sách các cặp (v, w) - đỉnh kề và trọng số
    vector<vector<pair<int, int>>> graph(n + 1);  // n+1 vì đỉnh bắt đầu từ 1
    
    // Bước 3: Đọc thông tin các cung và xây dựng đồ thị
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;        // Đọc cung từ u đến v với trọng số w
        graph[u].push_back({v, w}); // Thêm cung vào danh sách kề của u
    }
    
    // Bước 4: Đọc đỉnh nguồn và đỉnh đích
    int s, t;
    cin >> s >> t;  // s = start (nguồn), t = target (đích)
    
    // Bước 5: Khởi tạo mảng khoảng cách
    // dist[i] lưu khoảng cách ngắn nhất từ s đến i
    vector<long long> dist(n + 1, LLONG_MAX);  // Khởi tạo tất cả là vô cùng
    dist[s] = 0;  // Khoảng cách từ s đến chính nó là 0
    
    // Bước 6: Khởi tạo hàng đợi ưu tiên (min-heap)
    // Priority_queue sẽ lưu các cặp (khoảng cách, đỉnh)
    // greater<> để biến priority_queue thành min-heap (lấy phần tử nhỏ nhất)
    priority_queue<pair<long long, int>, 
                   vector<pair<long long, int>>, 
                   greater<pair<long long, int>>> pq;
    pq.push({0, s});  // Đẩy đỉnh nguồn vào heap với khoảng cách 0
    
    // Bước 7: Thuật toán Dijkstra - vòng lặp chính
    while (!pq.empty()) {
        // Lấy đỉnh có khoảng cách nhỏ nhất từ heap
        long long current_dist = pq.top().first;   // Khoảng cách từ s đến u
        int current_node = pq.top().second;        // Đỉnh u
        pq.pop();
        
        // QUAN TRỌNG: Nếu khoảng cách trong heap lớn hơn khoảng cách hiện tại
        // thì bỏ qua vì đã có đường đi tốt hơn đến đỉnh này
        if (current_dist > dist[current_node]) {
            continue;  // Bỏ qua và xét phần tử tiếp theo trong heap
        }
        
        // Duyệt tất cả các đỉnh kề của current_node
        for (auto &edge : graph[current_node]) {
            int neighbor = edge.first;     // Đỉnh kề v
            int weight = edge.second;      // Trọng số cung (u,v)
            
            // Tính khoảng cách từ s đến neighbor qua current_node
            long long new_dist = dist[current_node] + weight;
            
            // Nếu tìm được đường đi ngắn hơn đến neighbor
            if (new_dist < dist[neighbor]) {
                dist[neighbor] = new_dist;  // Cập nhật khoảng cách
                pq.push({new_dist, neighbor});  // Đẩy vào heap để xét sau
                // Lưu ý: Một đỉnh có thể được đẩy nhiều lần vào heap
                // Nhưng chỉ những lần với khoảng cách tốt hơn mới được xử lý
            }
        }
    }
    
    // Bước 8: In kết quả
    if (dist[t] == LLONG_MAX) {
        // Nếu khoảng cách vẫn là vô cùng -> không có đường đi từ s đến t
        cout << -1 << endl;
    } else {
        // In ra khoảng cách ngắn nhất từ s đến t
        cout << dist[t] << endl;
    }
    
    return 0;
}
