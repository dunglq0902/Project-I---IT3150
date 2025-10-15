#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

struct State {
    int x, y; // x: lượng nước trong bình a, y: lượng nước trong bình b
    int steps;
};

int a, b, c;
bool visited[1000][1000]; // Mảng đánh dấu trạng thái đã thăm

int solve() {
    queue<State> q; //queue lưu state, mỗi phần tử là trạng thái của bình 1,2 và steps
    q.push({0, 0, 0});//Lưu trạng thái ban đầu  
    visited[0][0] = true;
    
    while (!q.empty()) {
        State curr = q.front();//q.front(): lấy phần tử ở đầu hàng đợi mà không xóa nó
        q.pop();
        
        // Kiểm tra nếu đã đạt được c lít
        if (curr.x == c || curr.y == c) {
            return curr.steps;
        }

        // Các thao tác có thể thực hiện:
        
        // 1. Đổ đầy bình a
        if (!visited[a][curr.y]) {
            visited[a][curr.y] = true;
            q.push({a, curr.y, curr.steps + 1});
        }
        
        // 2. Đổ đầy bình b
        if (!visited[curr.x][b]) {
            visited[curr.x][b] = true;
            q.push({curr.x, b, curr.steps + 1});
        }
        
        // 3. Đổ hết bình a
        if (!visited[0][curr.y]) {
            visited[0][curr.y] = true;
            q.push({0, curr.y, curr.steps + 1});
        }
        
        // 4. Đổ hết bình b
        if (!visited[curr.x][0]) {
            visited[curr.x][0] = true;
            q.push({curr.x, 0, curr.steps + 1});
        }
        
        // 5. Đổ từ a sang b
        int pour = min(curr.x, b - curr.y);
        if (!visited[curr.x - pour][curr.y + pour]) {
            visited[curr.x - pour][curr.y + pour] = true;
            q.push({curr.x - pour, curr.y + pour, curr.steps + 1});
        }
        
        // 6. Đổ từ b sang a
        pour = min(curr.y, a - curr.x);
        if (!visited[curr.x + pour][curr.y - pour]) {
            visited[curr.x + pour][curr.y - pour] = true;
            q.push({curr.x + pour, curr.y - pour, curr.steps + 1});
        }
    }
    
    return -1; // Không tìm thấy giải pháp
}

int main() {
    cin >> a >> b >> c;
    memset(visited, false, sizeof(visited));
    //memset là một hàm trong C/C++ dùng để thiết lập một khối bộ nhớ với một giá trị cụ thể.
    //Kết quả: Tất cả phần tử của visited được gán giá trị false

    int result = solve();
    cout << result << endl;
    
    return 0;
}