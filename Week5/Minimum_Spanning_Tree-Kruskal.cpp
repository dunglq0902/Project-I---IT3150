#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

struct Edge {   //Cấu trúc Edge:
    int u, v, w;    //Lưu trữ thông tin cạnh: 2 đỉnh u, v và trọng số w
    bool operator<(const Edge& other) const //Dòng này định nghĩa toán tử so sánh < cho struct Edge, phục vụ cho hàm sort ở phía dưới
    {
        return w < other.w; //Toán tử < giúp sắp xếp các cạnh theo trọng số tăng dần
    }
};

int parent[MAXN], sz[MAXN];

int find(int x) 
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

bool unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    if (sz[x] < sz[y]) swap(x, y);
    parent[y] = x;
    sz[x] += sz[y];
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    
    // Sắp xếp các cạnh theo trọng số tăng dần
    sort(edges.begin(), edges.end());
    //Nếu không định nghĩa operator< trong struct Edge thì => LỖI! Không biết so sánh thế nào
    
    // Khởi tạo DSU: Disjoint Set Union
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    
    long long mst_weight = 0;
    int edges_used = 0;
    
    // Duyệt qua các cạnh theo thứ tự trọng số tăng dần
    for (const Edge& e : edges) {
        if (edges_used == n - 1) break;
        
        if (unite(e.u, e.v)) {
            mst_weight += e.w;
            edges_used++;
        }
    }
    
    cout << mst_weight << "\n";
    
    return 0;
}   