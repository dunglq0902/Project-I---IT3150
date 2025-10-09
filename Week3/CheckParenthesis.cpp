#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main(){
    string s;
    cin>>s;

    stack<char> st; // Tạo stack để lưu các dấu mở ngoặc

    for(char c: s){
        if(c == '(' || c =='{' || c == '['){
            st.push(c);
        }

        // Nếu là dấu đóng ngoặc
        else{
            if(st.empty()){
                cout<<0<<endl;
                return 0;
            }

            // Lấy dấu mở ngoặc trên đỉnh stack
            char top = st.top();
            if ((c == ')' && top == '(') ||
                (c == ']' && top == '[') ||
                (c == '}' && top == '{')) 
            {
                st.pop();  // Nếu khớp thì lấy dấu mở ra khỏi stack
            }
            else {
                // Nếu không khớp -> lỗi
                cout << 0;
                return 0; 
            }
        }
    }
    // Sau khi duyệt hết chuỗi, stack phải rỗng thì mới đúng
    if (st.empty()) {
        cout << 1;  // Tất cả dấu ngoặc đều khớp
    } else {
        cout << 0;  // Còn dấu mở ngoặc chưa được đóng
    }
    
    return 0;
}