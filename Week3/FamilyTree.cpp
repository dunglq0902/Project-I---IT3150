#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

map<string, vector<string>> family; // Lưu mỗi người và danh sách con của họ

// Hàm đếm tổng số con cháu
//? Truyền const string& name để truyền địa chỉ->tốc độ nhanh hơn và const=>không thay đổi name
int countDescendants(const string& name){
    if(family.find(name) == family.end()) // Nếu không có con
        return 0;

    int count = 0;
    for(const string& child : family[name]){
        count += 1 + countDescendants(child); // Đếm con và con cháu của con
    }
    return count;
}

// Hàm tìm số thế hệ (thế hệ sâu nhất)
int findMaxGeneration(const string& name) {
    if(family.find(name) == family.end()){
        return 0; //không có con
    }

    int maxGen = 0;
    for (const string& child : family[name]) {
        int childGen = findMaxGeneration(child);
        maxGen = max(maxGen, childGen);
    }
    return maxGen + 1; // +1 cho thế hệ hiện tại
}

int main(){
    string child, parent;

    // Đọc phần đầu: quan hệ cha-con
    while(cin>>child){
        if(child == "***")
            break;
        cin>>parent;
        family[parent].push_back(child); // Thêm con vào danh sách con của cha
    }

    //Xử lý truy vấn
    string cmd, param;
    while(cin>>cmd){
        if(cmd == "***")
            break;
        cin>>param;

        if(cmd == "descendants"){
            cout<<countDescendants(param)<<endl;
        }
        else if(cmd == "generation"){
            cout<<findMaxGeneration(param)<<endl;
        }
    }
    return 0;
}





// Description
// Given a family tree represented by child-parent (c,p) relations in which c is a child of p. Perform queries about the family tree:
// descendants <name>: return number of descendants of the given <name>
// generation <name>: return the number of generations of the descendants of the given <name>

// Note that: the total number of people in the family is less than or equal to 10
// 4
// Input
// Contains two blocks. The first block contains information about child-parent, including lines (terminated by a line containing ***), each line contains: <child> <parent> where <child> is a string represented the name of the child and <parent> is a string represented the name of the parent. The second block contains lines (terminated by a line containing ***), each line contains two string <cmd> and <param> where <cmd> is the command (which can be descendants or generation) and <param> is the given name of the person participating in the  query.
// Output
// Each line is the result of a corresponding query.
// Example
// Input
// Peter Newman
// Michael Thomas
// John David
// Paul Mark
// Stephan Mark
// Pierre Thomas
// Mark Newman
// Bill David
// David Newman
// Thomas Mark
// ***
// descendants Newman
// descendants Mark
// descendants David
// generation Mark
// ***
// Output
// 10
// 5
// 2
// 2