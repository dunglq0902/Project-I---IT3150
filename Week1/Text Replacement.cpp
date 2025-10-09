#include <iostream>
#include <string>
using namespace std;

int main() {
    string P1, P2;

    // Đọc chuỗi P1 và P2
    getline(cin, P1);
    getline(cin, P2);

    // Đọc phần văn bản T (từ dòng thứ 3 trở đi)
    string T = "", line;
    bool first = true;
    while (getline(cin, line)) {
        if (!first) {
            T += "\n";   // thêm xuống dòng giữa các dòng
        }
        T += line;
        first = false;
    }
    //Xử lý việc take input các dòng vào thành text T

    // Nếu P1 rỗng thì không thay thế gì
    if (P1 == "") {
        cout << T;
        return 0;
    }

    // Thay thế tất cả P1 bằng P2
    int pos = 0;
    while (true) {
        pos = T.find(P1, pos);       // tìm P1 trong T từ vị trí pos
        if (pos == -1) 
            break;        //không tìm thấy thì dừng
        T.replace(pos, P1.length(), P2); // thay P1 bằng P2
        pos += P2.length();          // nhảy qua phần vừa thay để tránh lặp vô tận
    }

    // In kết quả
    cout << T;

    return 0;
}

// Description
// Cho văn bản T và 2 mẫu P1, P2 đều là các xâu ký tự (không chứa ký tự xuống dòng, độ dài không vượt quá 1000). Hãy thay thế các xâu P1 trong T bằng xâu P2.
// Dữ liệu
// · Dòng 1: xâu P1
// · Dòng 2: xâu P2
// · Dòng 3: văn bản T
// Kết quả:
// · Ghi văn bản T sau khi thay thế
// Ví dụ
// Dữ liệu
// AI
// Artificial Intelligence
// Recently, AI is a key technology. AI enable efficient operations in many fields.
// Kết quả
// Recently, Artificial Intelligence is a key technology. Artificial Intelligence enable efficient operations in many fields.