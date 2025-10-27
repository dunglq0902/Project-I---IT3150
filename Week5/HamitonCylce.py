import sys  # là câu lệnh dùng để nhập module sys
# điều khiển các chức năng như thoát khỏi chương trình (sys.exit()), 
# làm việc với đối số dòng lệnh (sys.argv) hoặc truy cập các luồng đầu vào/đầu ra tiêu chuẩn. 

def hamiltonian_cycle(start, current, count, visited, adj, n):
    # Nếu đã đi qua tất cả các đỉnh
    if count == n:
        # Kiểm tra xem đỉnh hiện tại có kề với đỉnh xuất phát không
        if start in adj[current]:
            return True
        return False
    
    # Duyệt qua tất cả các đỉnh kề
    for neighbor in adj[current]:
        if not visited[neighbor]:
            visited[neighbor] = True
            if hamiltonian_cycle(start, neighbor, count + 1, visited, adj, n):
                return True
            visited[neighbor] = False
    
    return False

def is_hamiltonian(n, adj):
    # Kiểm tra từ mỗi đỉnh làm điểm bắt đầu
    for start in range(1, n + 1):
        visited = [False] * (n + 1)
        visited[start] = True
        if hamiltonian_cycle(start, start, 1, visited, adj, n):
            return True
    return False

def main():
    data = sys.stdin.read().strip().split()
    #Đọc toàn bộ input từ stdin
    #strip(): loại bỏ khoảng trắng thừa
    #split(): tách thành danh sách các từ

    if not data:
        return
    
    t = int(data[0])
    index = 1
    results = []
    
    for _ in range(t):
        n = int(data[index]); m = int(data[index + 1])
        index += 2
        
        # Khởi tạo danh sách kề
        adj = [[] for _ in range(n + 1)]
        
        # Đọc các cạnh
        for i in range(m):
            u = int(data[index]); v = int(data[index + 1])  #Đọc số đỉnh n và số cạnh m
            index += 2  #Tăng index để đọc tiếp các cạnh
            adj[u].append(v)
            adj[v].append(u)
        
        # Kiểm tra và lưu kết quả
        if is_hamiltonian(n, adj):
            results.append(1)
        else:
            results.append(0)
    
    # In kết quả
    for res in results:
        print(res)

if __name__ == "__main__":
    main()