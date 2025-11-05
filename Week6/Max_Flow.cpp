#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

// Định nghĩa cấu trúc 1 cung trong đồ thị
struct Edge {
    int v;        // Đỉnh đích
    int capacity; // Khả năng thông qua tối đa
    int flow;     // Luồng hiện tại đang chảy
    int rev;      // Chỉ số của cung ngược trong danh sách kề của đỉnh đích
};

class Dinic {
private:
    int n, s, t;                    // Số đỉnh, nguồn, đích
    vector<vector<Edge>> graph;     // Danh sách kề của đồ thị
    vector<int> level;              // Mức độ (khoảng cách) từ nguồn
    vector<int> ptr;                // Con trỏ DFS cho mỗi đỉnh
    
    // Hàm BFS để xây dựng đồ thị phân tầng
    bool bfs() {
        fill(level.begin(), level.end(), -1);  // Khởi tạo tất cả level = -1 (chưa thăm)
        queue<int> q;
        q.push(s);              // Đẩy đỉnh nguồn vào queue
        level[s] = 0;           // Nguồn có level = 0
        
        while (!q.empty()) {
            int u = q.front();   // Lấy đỉnh đầu queue
            q.pop();
            
            // Duyệt tất cả cung đi từ u
            for (Edge &e : graph[u]) {
                // Nếu đỉnh e.v chưa được thăm VÀ cung này còn khả năng thông qua
                if (level[e.v] == -1 && e.flow < e.capacity) {
                    level[e.v] = level[u] + 1;  // Gán level = level[u] + 1
                    q.push(e.v);                // Đẩy vào queue để duyệt tiếp
                }
            }
        }
        return level[t] != -1;  // Trả về true nếu tìm được đường đến đích
    }
    
    // Hàm DFS để tìm và đẩy luồng
    int dfs(int u, int pushed) {
        // Nếu đã đến đích hoặc không thể đẩy thêm luồng
        if (u == t || pushed == 0) return pushed;
        
        // Duyệt các cung từ u, bắt đầu từ vị trí ptr[u]
        for (int &cid = ptr[u]; cid < graph[u].size(); cid++) {
            Edge &e = graph[u][cid];  // Tham chiếu đến cung hiện tại
            
            // Kiểm tra: đỉnh đích phải có level cao hơn đúng 1 VÀ cung còn khả năng thông qua
            if (level[e.v] == level[u] + 1 && e.flow < e.capacity) {
                // Gọi đệ quy để tìm luồng có thể đẩy từ e.v đến đích
                int tr = dfs(e.v, min(pushed, e.capacity - e.flow));
                
                // Nếu tìm được luồng > 0
                if (tr > 0) {
                    e.flow += tr;                       // Tăng luồng trên cung thuận
                    graph[e.v][e.rev].flow -= tr;       // Giảm luồng trên cung ngược
                    return tr;                          // Trả về luồng vừa đẩy được
                }
            }
        }
        return 0;  // Không tìm được đường nào
    }
    
public:
    // Constructor: khởi tạo đồ thị với n đỉnh, nguồn s, đích t
    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        graph.resize(n + 1);   // Cấp phát cho n+1 đỉnh (từ 1 đến n)
        level.resize(n + 1);   // Mảng level cho n+1 đỉnh
        ptr.resize(n + 1);     // Mảng con trỏ cho n+1 đỉnh
    }
    
    // Thêm cung từ u đến v với khả năng thông qua = capacity
    void addEdge(int u, int v, int capacity) {
        // Tạo cung thuận: u → v
        Edge e1 = {v, capacity, 0, (int)graph[v].size()};
        // Tạo cung ngược: v → u (ban đầu capacity = 0)
        Edge e2 = {u, 0, 0, (int)graph[u].size()};
        
        // Thêm cung thuận vào danh sách kề của u
        graph[u].push_back(e1);
        // Thêm cung ngược vào danh sách kề của v
        graph[v].push_back(e2);
    }
    
    // Hàm chính tính luồng cực đại
    int maxFlow() {
        int totalFlow = 0;  // Tổng luồng = 0 ban đầu
        
        // Lặp cho đến khi không còn đường tăng luồng
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);  // Reset tất cả con trỏ về 0
            
            // Đẩy luồng nhiều lần cho đến khi không đẩy được nữa
            while (int pushed = dfs(s, INT_MAX)) {
                totalFlow += pushed;  // Cộng dồn luồng vào tổng
            }
        }
        return totalFlow;  // Trả về luồng cực đại
    }
};

int main() {
    // Tối ưu hóa tốc độ nhập xuất
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, s, t;
    cin >> n >> m >> s >> t;  // Đọc số đỉnh, số cung, nguồn, đích
    
    // Khởi tạo đối tượng Dinic
    Dinic dinic(n, s, t);
    
    // Đọc m cung và thêm vào đồ thị
    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        dinic.addEdge(u, v, c);  // Thêm cung u→v với capacity = c
    }
    
    // Tính và in luồng cực đại
    cout << dinic.maxFlow() << endl;
    
    return 0;
}
