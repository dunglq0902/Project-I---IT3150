#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main(){
    queue<int> q; // Tạo một hàng đợi rỗng để lưu các số nguyên
    string line;

    while(cin>>line)
    {
        if(line == "#")
            break;

        if(line == "PUSH"){
            int val;
            cin>>val;
            q.push(val); // Thêm giá trị vào cuối hàng đợi

        }
        else if(line == "POP" && !q.empty()){
            cout<<q.front()<<endl;
            q.pop();
        }
        else
            cout<<"NULL"<<endl; // In NULL nếu hàng đợi rỗng
    }
    return 0;
}