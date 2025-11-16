#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

// Định nghĩa cấu trúc lưu trữ thông tin một đơn hàng
struct Order {
    string customerID;   
    string productID;    
    int price;           
    string shopID;      
    string timePoint;   
};

int main() {
    // Các cấu trúc dữ liệu để lưu trữ và thống kê
    vector<Order> orders;
    map<string, int> shopRevenue;
    map<pair<string, string>, int> customerShopRevenue;
    int totalOrders = 0;  
    int totalRevenue = 0;

    // --- ĐỌC DỮ LIỆU ĐƠN HÀNG ---
    string line;
    while (getline(cin, line)) {
        if (line == "#") 
            break;  // Kết thúc khối dữ liệu khi gặp #
        
        istringstream ss(line);  // Dùng stringstream để tách dữ liệu
        Order o;
        // Đọc các trường thông tin từ dòng dữ liệu
        ss >> o.customerID >> o.productID >> o.price >> o.shopID >> o.timePoint;
        
        // Lưu đơn hàng vào danh sách
        orders.push_back(o);
        
        // Cập nhật các thống kê
        totalOrders++;                         
        totalRevenue += o.price;               
        shopRevenue[o.shopID] += o.price;      
        customerShopRevenue[{o.customerID, o.shopID}] += o.price;  
    }

    // --- CHUẨN BỊ CHO TRUY VẤN THEO THỜI GIAN ---
    vector<pair<string, int>> timePrice;  // Lưu cặp (thời gian, giá) để sắp xếp
    
    // Chuyển đổi dữ liệu đơn hàng sang dạng phù hợp cho truy vấn thời gian
    for (auto& o : orders) {
        timePrice.push_back({o.timePoint, o.price});
    }
        
    // Sắp xếp danh sách theo thời gian tăng dần
    sort(timePrice.begin(), timePrice.end());

    // Xây dựng mảng prefix sum để truy vấn tổng nhanh
    vector<int> prefixSum(timePrice.size() + 1, 0);
    for (int i = 0; i < timePrice.size(); i++) {
        prefixSum[i + 1] = prefixSum[i] + timePrice[i].second;
    }

    // --- XỬ LÝ CÁC TRUY VẤN ---
    while (getline(cin, line)) {
        if (line == "#") break;  // Kết thúc khi gặp #
        
        istringstream ss(line);
        string cmd;
        ss >> cmd;  // Đọc loại truy vấn

        // TRUY VẤN 1: Tổng số đơn hàng
        if (cmd == "?total_number_orders") {
            cout << totalOrders << "\n";
        }
        // TRUY VẤN 2: Tổng doanh thu công ty
        else if (cmd == "?total_revenue") {
            cout << totalRevenue << "\n";
        }
        // TRUY VẤN 3: Doanh thu của một cửa hàng cụ thể
        else if (cmd == "?revenue_of_shop") {
            string shop;
            ss >> shop;  // Đọc mã cửa hàng từ truy vấn
            cout << shopRevenue[shop] << "\n";  // Tra cứu trong map
        }
        // TRUY VẤN 4: Tổng chi tiêu của khách hàng tại một cửa hàng
        else if (cmd == "?total_consume_of_customer_shop") {
            string customer, shop;
            ss >> customer >> shop;  // Đọc mã khách hàng và cửa hàng
            cout << customerShopRevenue[{customer, shop}] << "\n";  // Tra cứu trong map
        }
        // TRUY VẤN 5: Doanh thu trong khoảng thời gian
        else if (cmd == "?total_revenue_in_period") {
            string fromTime, toTime;
            ss >> fromTime >> toTime;  // Đọc thời gian bắt đầu và kết thúc
            
            // Tìm vị trí đầu tiên có thời gian >= fromTime
            int lo = lower_bound(timePrice.begin(), timePrice.end(), 
                                make_pair(fromTime, 0)) - timePrice.begin();
            
            // Tìm vị trí đầu tiên có thời gian > toTime
            int hi = upper_bound(timePrice.begin(), timePrice.end(),
                                make_pair(toTime, 1000000)) - timePrice.begin();
            
            // Tính tổng doanh thu trong khoảng [lo, hi-1] bằng prefix sum
            int sum = prefixSum[hi] - prefixSum[lo];
            cout << sum << "\n";
        }
    }

    return 0;
}