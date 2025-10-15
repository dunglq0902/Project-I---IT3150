#include<iostream>
#include<stack>
#include<string>
using namespace std;
int main()
{
    stack<int> s;
    string line;

    while(cin>> line){
        if(line == "#")
            break;
        if(line == "PUSH"){
            int v;
            cin>>v;
            s.push(v);
        }
        else if(line == "POP"){
            if(s.empty())
                cout<<"NULL";
            else{
                cout << s.top()<<endl;
                s.pop();
            }
        }
    }
}