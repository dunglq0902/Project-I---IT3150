#include <iostream> 
#include <string>
#include <vector>  
#include <map>      // Dùng để lưu trữ ánh xạ (ví dụ: tài khoản -> tổng tiền gửi)
#include <set>      // Dùng để lưu trữ các tài khoản duy nhất (và tự động sắp xếp)
#include <sstream>  // Dùng để đọc dữ liệu từ một dòng (string)
#include <iomanip>  // dùng để định dạng output)

using namespace std;

// Cấu trúc dữ liệu toàn cục để lưu trữ thông tin
long long total_money_transaction = 0;
int number_transactions = 0;
set<string> accounts; // Tự động sắp xếp và đảm bảo duy nhất
map<string, long long> money_from; // Key: from_account, Value: tổng tiền đã gửi
map<string, set<string>> adj; // Danh sách kề của đồ thị giao dịch

/**
 * @brief Hàm tìm kiếm chu trình bằng DFS (Depth First Search - Tìm kiếm theo chiều sâu).
 * * @param current Tài khoản hiện tại đang thăm
 * @param target Tài khoản bắt đầu (mục tiêu cần quay về)
 * @param k Độ dài chu trình (số đỉnh)
 * @param current_depth Độ sâu hiện tại của đường đi (số đỉnh đã đi qua)
 * @param path_visited Set chứa các đỉnh đã thăm trong đường đi hiện tại
 * @return true nếu tìm thấy chu trình độ dài k, false nếu không.
 */

bool find_cycle(string current, string target, int k, int current_depth, set<string>& path_visited) {
    // Đánh dấu đã thăm đỉnh hiện tại
    path_visited.insert(current);

    // Duyệt qua tất cả các "hàng xóm" (tài khoản được chuyển đến)
    if (adj.count(current)) { // Kiểm tra xem tài khoản này có chuyển tiền đi không
        for (const string& next_node : adj[current]) {
            // Trường hợp 1: Đã quay về đỉnh bắt đầu
            if (next_node == target) {
                // Nếu độ sâu (số đỉnh) bằng k, ta đã tìm thấy chu trình
                if (current_depth == k) {
                    return true;
                }
                // Nếu không, đây là chu trình ngắn hơn, bỏ qua
            }
            // Trường hợp 2: Đi tiếp đến đỉnh mới
            // Chỉ đi tiếp nếu đỉnh tiếp theo chưa có trong đường đi hiện tại
            // và đường đi hiện tại chưa đạt đến độ dài k-1 (vì đỉnh tiếp theo sẽ là k)
            else if (path_visited.find(next_node) == path_visited.end()) {
                if (current_depth < k) {
                    if (find_cycle(next_node, target, k, current_depth + 1, path_visited)) {
                        return true; // Lan truyền kết quả tìm thấy
                    }
                }
            }
        }
    }

    // Backtrack: Bỏ đánh dấu đỉnh hiện tại khi thoát khỏi đệ quy
    path_visited.erase(current);
    return false;
}

int main() {
    // Tăng tốc độ nhập xuất
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string line;

    // --- KHỐI ĐỌC DỮ LIỆU ---
    while (getline(cin, line) && line != "#") {
        stringstream ss(line);
        string from_account, to_account, time_point, atm;
        int money;

        ss >> from_account >> to_account >> money >> time_point >> atm;

        // Cập nhật các biến thống kê
        number_transactions++;
        total_money_transaction += money;

        // Thêm tài khoản vào set (nếu chưa có)
        accounts.insert(from_account);
        accounts.insert(to_account);

        // Cập nhật tổng tiền gửi từ from_account
        money_from[from_account] += money;

        // Thêm cạnh vào đồ thị
        adj[from_account].insert(to_account);
    }

    // --- KHỐI XỬ LÝ TRUY VẤN ---
    while (getline(cin, line) && line != "#") {
        stringstream ss(line);
        string query_cmd;
        ss >> query_cmd;

        if (query_cmd == "?number_transactions") {
            cout << number_transactions << "\n";
        } 
        else if (query_cmd == "?total_money_transaction") {
            cout << total_money_transaction << "\n";
        } 
        else if (query_cmd == "?list_sorted_accounts") {
            // In tất cả các tài khoản, cách nhau bởi dấu cách
            // (Set tự động sắp xếp)
            bool first = true;
            for (const string& acc : accounts) {
                if (!first) {
                    cout << " ";
                }
                cout << acc;
                first = false;
            }
            cout << "\n";
        } 
        else if (query_cmd == "?total_money_transaction_from") {
            string account;
            ss >> account;
            // Nếu tài khoản không có trong map 'money_from' (chưa gửi tiền lần nào),
            // map[key] sẽ tự động tạo giá trị 0.
            cout << money_from[account] << "\n";
        } 
        else if (query_cmd == "?inspect_cycle") {
            string start_account;
            int k;
            ss >> start_account >> k;

            set<string> path_visited; // Set để theo dõi đường đi hiện tại
            // Bắt đầu DFS với độ sâu là 1 (tại đỉnh start_account)
            if (find_cycle(start_account, start_account, k, 1, path_visited)) {
                cout << 1 << "\n";
            } else {
                cout << 0 << "\n";
            }
        }
    }

    return 0;
}