/*
 * Giải pháp C++ TỐI ƯU cho bài toán Quản lý Submission.
 * Sử dụng map để truy cập O(log N) và tìm kiếm nhị phân
 * cho các truy vấn phạm vi thời gian O(log N).
 */
#include <iostream>  // Dùng cho cin, cout
#include <string>    // Dùng cho kiểu string
#include <vector>    // Dùng để lưu trữ thời gian (cho tìm kiếm nhị phân)
#include <map>       // Dùng để lưu trữ dữ liệu theo UserID, ProblemID
#include <sstream>   // Dùng để xử lý chuỗi (đọc từng phần tử trên một dòng)
#include <algorithm> // Dùng cho sort, lower_bound, upper_bound

using namespace std;

// --- Cấu trúc dữ liệu toàn cục ---

// Query 1: ?total_number_submissions
int total_submissions = 0;

// Query 2: ?number_error_submision
int total_errors = 0;

// Query 3: ?number_error_submision_of_user
// Key: UserID, Value: số lần nộp lỗi
map<string, int> user_errors;

// Query 4: ?total_point_of_user
// Key: UserID, Value: (map: Key: ProblemID, Value: max_point)
map<string, map<string, int>> user_problem_max_points;

// Query 5: ?number_submission_period
// Lưu trữ tất cả các mốc thời gian để sắp xếp và tìm kiếm nhị phân
vector<string> submission_times;


int main() {
    // Tăng tốc độ nhập/xuất (Rất quan trọng cho 100,000 dòng)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string line;

    // --- KHỐI 1: ĐỌC VÀ TIỀN XỬ LÝ DỮ LIỆU ---
    while (getline(cin, line) && line != "#") {
        stringstream ss(line);
        string userID, problemID, timePoint, status;
        int point;

        ss >> userID >> problemID >> timePoint >> status >> point;

        // Xử lý cho Query 1: O(1)
        total_submissions++;

        // Xử lý cho Query 2 & 3: O(log N_users)
        if (status == "ERR") {
            total_errors++;
            user_errors[userID]++; // map sẽ tự khởi tạo 0 nếu chưa có
        }

        // Xử lý cho Query 4: O(log N_users + log N_problems)
        // Lấy điểm tối đa hiện tại của user cho bài này
        int current_max = user_problem_max_points[userID][problemID]; // Tự khởi tạo 0
        if (point > current_max) {
            user_problem_max_points[userID][problemID] = point;
        }

        // Xử lý cho Query 5 (Thu thập dữ liệu): O(1)
        submission_times.push_back(timePoint);
    }

    // --- TIỀN XỬ LÝ CHO QUERY 5 ---
    // Sắp xếp vector thời gian MỘT LẦN.
    // Đây là bước then chốt để tối ưu truy vấn thời gian.
    // Độ phức tạp: O(S log S) với S là số lần nộp bài.
    sort(submission_times.begin(), submission_times.end());


    // --- KHỐI 2: ĐỌC VÀ XỬ LÝ TRUY VẤN ---
    while (getline(cin, line) && line != "#") {
        stringstream ss(line);
        string query_cmd;
        ss >> query_cmd;

        if (query_cmd == "?total_number_submissions") {
            // O(1)
            cout << total_submissions << "\n";
        } 
        else if (query_cmd == "?number_error_submision") {
            // O(1)
            cout << total_errors << "\n";
        } 
        else if (query_cmd == "?number_error_submision_of_user") {
            // O(log N_users)
            string userID;
            ss >> userID;
            cout << user_errors[userID] << "\n"; // Tự trả về 0 nếu user không có lỗi
        } 
        else if (query_cmd == "?total_point_of_user") {
            // O(log N_users + N_problems_for_user) - Rất nhanh
            string userID;
            ss >> userID;
            
            int total_points = 0;
            // Chỉ duyệt qua map các bài của user đó
            if (user_problem_max_points.count(userID)) {
                // Duyệt qua tất cả các cặp (ProblemID, max_point) của user
                for (auto const& [problem, points] : user_problem_max_points[userID]) {
                    total_points += points;
                }
            }
            cout << total_points << "\n";
        } 
        else if (query_cmd == "?number_submission_period") {
            // O(log S) - Tối ưu nhất
            string from_time, to_time;
            ss >> from_time >> to_time;
            
            // Tìm con trỏ đến phần tử ĐẦU TIÊN >= from_time
            auto it_from = lower_bound(submission_times.begin(), 
                                       submission_times.end(), 
                                       from_time);
            
            // Tìm con trỏ đến phần tử ĐẦU TIÊN > to_time
            auto it_to = upper_bound(submission_times.begin(), 
                                     submission_times.end(), 
                                     to_time);
            
            // Kết quả là khoảng cách giữa hai con trỏ
            cout << (it_to - it_from) << "\n";
        }
    }

    return 0;
}
