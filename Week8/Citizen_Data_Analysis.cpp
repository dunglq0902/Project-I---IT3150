#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <queue>

using namespace std;

/**
 * @brief Cấu trúc lưu trữ thông tin cơ bản của một người.
 */
struct Person {
    string code;
    string dob;
    string father_code;
    string mother_code;
    char is_alive;
    // region_code không cần thiết cho các truy vấn
};

// --- CÁC CẤU TRÚC DỮ LIỆU TOÀN CỤC ---

// Query 1: NUMBER_PEOPLE
int total_people = 0;

// Query 2 & 4: NUMBER_PEOPLE_BORN_AT / BETWEEN
// Key: "YYYY-MM-DD", Value: số người sinh vào ngày đó
map<string, int> birth_date_count;

// *** FIX TLE ***: Thêm map tổng tiền tố cho truy vấn NUMBER_PEOPLE_BORN_BETWEEN
// Key: "YYYY-MM-DD", Value: tổng số người sinh TÍNH ĐẾN ngày đó
map<string, int> birth_date_prefix_sum;

// Query 3: MOST_ALIVE_ANCESTOR
// Key: "code", Value: đối tượng Person
map<string, Person> database;

// Query 5: MAX_UNRELATED_PEOPLE
// Key: parent_code, Value: danh sách children_code
map<string, vector<string>> children_of;

// *** FIX WA: Thêm các cấu trúc để phân chia đồ thị hai phía ***
set<string> has_parent; // Dùng để tìm gốc (người không có cha mẹ)
map<string, int> level; // Dùng để lưu thế hệ (chẵn/lẻ)
set<string> U_partition; // Tập "thế hệ chẵn" (level 0, 2, 4...)
set<string> V_partition; // Tập "thế hệ lẻ" (level 1, 3, 5...)


/**
 * @brief Hàm DFS để tìm đường tăng cho thuật toán cặp ghép (Kuhn's Algorithm).
 * *** FIX WA ***:
 * Bổ sung tham số V_partition để đảm bảo chỉ ghép với các nút ở phía bên kia.
 */
bool dfs_match(const string& u_left, set<string>& visited_right, 
               map<string, string>& match_from_right, 
               const set<string>& V_partition) { // Thêm tham số
    
    // Nếu u_left không có con, không thể ghép
    if (children_of.find(u_left) == children_of.end()) {
        return false;
    }

    // Duyệt qua các con 'v_right' của 'u_left'
    for (const string& v_right : children_of.at(u_left)) {
        
        // *** THÊM KIỂM TRA ***
        // Chỉ ghép nếu 'v_right' (đứa con) nằm ở phân hoạch CÒN LẠI (V)
        if (V_partition.find(v_right) == V_partition.end()) {
            continue; // Đứa con này ở cùng phía (U), bỏ qua
        }

        if (visited_right.find(v_right) == visited_right.end()) {
            visited_right.insert(v_right);

            // Nếu 'v_right' chưa được ghép, HOẶC có thể tìm đường tăng cho
            // parent 'u_prime' đang ghép với 'v_right'
            if (match_from_right.find(v_right) == match_from_right.end() || 
                dfs_match(match_from_right[v_right], visited_right, match_from_right, V_partition)) { // Đệ quy
                
                match_from_right[v_right] = u_left; // Ghép u_left -> v_right
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Giải quyết truy vấn MOST_ALIVE_ANCESTOR bằng BFS.
 * @param start_code Mã của người bắt đầu tìm.
 */
void solve_most_alive_ancestor(const string& start_code) {
    queue<pair<string, int>> q; // <person_code, generation>
    set<string> visited;
    int max_alive_gen = 0;

    // Nếu người này không có trong DB, trả về 0
    if (database.find(start_code) == database.end()) {
        cout << 0 << "\n";
        return;
    }

    Person p = database.at(start_code);
    
    // Bắt đầu BFS từ cha và mẹ (thế hệ 1)
    if (p.father_code != "0000000") {
        q.push({p.father_code, 1});
        visited.insert(p.father_code);
    }
    if (p.mother_code != "0000000") {
        q.push({p.mother_code, 1});
        visited.insert(p.mother_code);
    }

    while (!q.empty()) {
        string curr_code = q.front().first;
        int curr_gen = q.front().second;
        q.pop();

        // Nếu tổ tiên này không có trong DB, bỏ qua
        if (database.find(curr_code) == database.end()) {
            continue;
        }

        Person ancestor = database.at(curr_code);

        // Kiểm tra xem có còn sống và là thế hệ xa nhất không
        if (ancestor.is_alive == 'Y') {
            if (curr_gen > max_alive_gen) {
                max_alive_gen = curr_gen;
            }
        }

        // Thêm cha/mẹ của tổ tiên này vào hàng đợi (thế hệ + 1)
        string father = ancestor.father_code;
        if (father != "0000000" && visited.find(father) == visited.end()) {
            q.push({father, curr_gen + 1});
            visited.insert(father);
        }
        string mother = ancestor.mother_code;
        if (mother != "0000000" && visited.find(mother) == visited.end()) {
            q.push({mother, curr_gen + 1});
            visited.insert(mother);
        }
    }
    cout << max_alive_gen << "\n";
}

int main() {
    // Tăng tốc độ nhập/xuất
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    // --- KHỐI 1: ĐỌC DỮ LIỆU ---
    string line;
    while (getline(cin, line) && line != "*") {
        stringstream ss(line);
        Person p;
        string region_code; // Không dùng đến

        ss >> p.code >> p.dob >> p.father_code >> p.mother_code >> p.is_alive >> region_code;

        // Query 1
        total_people++;

        // Query 2 & 4
        birth_date_count[p.dob]++;

        // Query 3
        database[p.code] = p;

        // Query 5
        if (p.father_code != "0000000") {
            children_of[p.father_code].push_back(p.code);
            has_parent.insert(p.code); // *** FIX WA: Đánh dấu người này có cha
        }
        if (p.mother_code != "0000000") {
            children_of[p.mother_code].push_back(p.code);
            has_parent.insert(p.code); // *** FIX WA: Đánh dấu người này có mẹ
        }
    }

    // --- *** FIX TLE ***: TÍNH TOÁN TỔNG TIỀN TỐ ---
    // Thực hiện sau khi đọc hết dữ liệu và trước khi xử lý truy vấn
    int running_total = 0;
    for (auto const& [date, count] : birth_date_count) {
        running_total += count;
        birth_date_prefix_sum[date] = running_total;
    }

    // *** FIX WA: PHÂN CHIA ĐỒ THỊ BẰNG BFS ***
    queue<string> q_bfs;
    // 1. Tìm tất cả các gốc (không có cha mẹ)
    for (const auto& pair : database) {
        if (has_parent.find(pair.first) == has_parent.end()) {
            q_bfs.push(pair.first);
            level[pair.first] = 0;
            U_partition.insert(pair.first);
        }
    }

    // 2. Chạy BFS để gán level (thế hệ)
    while (!q_bfs.empty()) {
        string u = q_bfs.front();
        q_bfs.pop();
        int u_level = level[u];

        if (children_of.find(u) == children_of.end()) continue;

        for (const string& v : children_of.at(u)) {
            if (level.find(v) == level.end()) { // Nếu chưa thăm
                int v_level = u_level + 1;
                level[v] = v_level;
                if (v_level % 2 == 0) {
                    U_partition.insert(v);
                } else {
                    V_partition.insert(v);
                }
                q_bfs.push(v);
            }
        }
    }


    // --- KHỐI 2: XỬ LÝ TRUY VẤN ---
    string cmd;
    while (cin >> cmd && cmd != "***") {
        if (cmd == "NUMBER_PEOPLE") {
            cout << total_people << "\n";
        } 
        else if (cmd == "NUMBER_PEOPLE_BORN_AT") {
            string date;
            cin >> date;
            // map[key] sẽ trả về 0 nếu key không tồn tại
            cout << birth_date_count[date] << "\n";
        } 
        else if (cmd == "MOST_ALIVE_ANCESTOR") {
            string code;
            cin >> code;
            solve_most_alive_ancestor(code);
        } 
        else if (cmd == "NUMBER_PEOPLE_BORN_BETWEEN") {
            string from_date, to_date;
            cin >> from_date >> to_date;
            
            // --- *** FIX TLE ***: SỬ DỤNG PREFIX SUM ---
            // Tìm tổng số người sinh TÍNH ĐẾN to_date
            map<string, int>::iterator it_to = birth_date_prefix_sum.upper_bound(to_date);
            int total_at_to = 0;
            // Nếu it_to không phải là đầu, lùi 1 để lấy giá trị <= to_date
            if (it_to != birth_date_prefix_sum.begin()) {
                total_at_to = (--it_to)->second;
            }

            // Tìm tổng số người sinh TÍNH ĐẾN 1 ngày TRƯỚC from_date
            map<string, int>::iterator it_from = birth_date_prefix_sum.lower_bound(from_date);
            int total_before_from = 0;
            // Nếu it_from không phải là đầu, lùi 1 để lấy giá trị < from_date
            if (it_from != birth_date_prefix_sum.begin()) {
                total_before_from = (--it_from)->second;
            }
            
            cout << total_at_to - total_before_from << "\n";
        } 
        else if (cmd == "MAX_UNRELATED_PEOPLE") {
            // --- *** FIX WA ***: SỬ DỤNG ĐÚNG ĐỒ THỊ HAI PHÍA (U, V) ---
            
            map<string, string> match_from_right; // Ánh xạ: v (V_partition) -> u (U_partition)
            int matching_size = 0;
            
            // Chạy thuật toán Kuhn/DFS từ tập U (thế hệ chẵn)
            for (const string& u_left : U_partition) {
                set<string> visited_right; // Reset visited cho mỗi lần tìm đường tăng mới
                if (dfs_match(u_left, visited_right, match_from_right, V_partition)) {
                    matching_size++;
                }
            }
            
            // Kết quả (Max Independent Set) = |V| - |M|
            // |V| = total_people
            cout << total_people - matching_size << "\n";
        }
    }

    return 0;
}
