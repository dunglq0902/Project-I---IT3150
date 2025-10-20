#include <iostream>
#include <unordered_set>
#include <string>
using namespace std;
int main(){
    unordered_set<string> database;
    string key;

    while(cin >> key){
        if(key == "*")
            break;
        database.insert(key);
    }

    string cmd, findkey;
    
    while(cin>>cmd){
        if(cmd == "***")
            break;
        cin>>findkey;
        if(cmd == "find"){
            if(database.find(findkey) != database.end()){
                cout<<1<<endl;
            }
            else
                cout<<0<<endl;
        }
        if(cmd == "insert"){
            if(database.find(findkey) != database.end())
                cout<<0<<endl;
            else{
                database.insert(findkey);
                cout<<1<<endl;
            }
        }
    }
    return 0;
}