import sys
sys.setrecursionlimit(200000)  # Tăng giới hạn đệ quy cho input lớn

def dfs(u, adj, visited, result):
    visited[u] = True
    result.append(u)
    
    for v in adj[u]:
        if not visited[v]:
            dfs(v, adj, visited, result)

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    
    n = int(data[0])
    m = int(data[1])
    
    # Khởi tạo danh sách kề
    adj = [[] for _ in range(n + 1)]
    
    # Đọc các cạnh
    index = 2
    for i in range(m):
        u = int(data[index])
        v = int(data[index + 1])
        index += 2
        adj[u].append(v)
        adj[v].append(u)
    
    # Sắp xếp danh sách kề theo thứ tự từ điển
    for i in range(1, n + 1):
        adj[i].sort()
    
    # Khởi tạo mảng visited và kết quả
    visited = [False] * (n + 1)
    result = []
    
    # Duyệt DFS từ đỉnh 1
    dfs(1, adj, visited, result)
        
    # In kết quả
    print(' '.join(map(str, result)))

if __name__ == "__main__":
    main()