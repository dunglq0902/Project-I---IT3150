#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

// Cấu trúc một nút trên cây
struct Node {
    int id;
    vector<Node*> children;         //children: danh sách các con của nút (lưu con trỏ)
    
    Node(int _id) : id(_id) {}      //Constructor Node(int _id): khởi tạo nút với id cho trước
};

// Biến toàn cục
Node* root = NULL;                  //con trỏ đến nút gốc của cây, ban đầu là NULL
map<int, Node*> allNodes;           //map để truy cập nhanh các nút theo id
//Key: id của nút (số nguyên)
//Value: con trỏ đến nút đó


// Tạo nút gốc
void makeRoot(int u) {
    if (allNodes.find(u) != allNodes.end()) //allNodes.end() => trả về iterator phía sau của phần tử cuối cùng 
        return;//ý nghĩa dòng if là u đã TỒN TẠI
    //find(u) trả về iterator(con trỏ) đến phần từ có key = u

    //u chưa tồn tại
    root = new Node(u);
    allNodes[u] = root; // lưu con trỏ root vào map allNodes với key là u.
}

// Thêm nút u là con của nút v
void insertNode(int u, int v) {
    if (allNodes.find(u) != allNodes.end() || allNodes.find(v) == allNodes.end()) {
        return; //Nếu đã tồn tại u hoặc không tồn tại v thì không chèn thêm mới
    }
    
    Node* newNode = new Node(u);
    Node* parentNode = allNodes[v]; //lấy con trỏ đến nút cha (nút v)
    parentNode->children.push_back(newNode);
    allNodes[u] = newNode;
}

// Duyệt theo thứ tự trước
void preOrder(Node* node, vector<int>& result) {
    if (node == NULL) return;
    
    result.push_back(node->id);
    for (Node* child : node->children) {
        preOrder(child, result);
    }
}

// Duyệt theo thứ tự giữa
void inOrder(Node* node, vector<int>& result) {
    if (node == NULL) return;
    
    if (!node->children.empty()) {
        inOrder(node->children[0], result);
    }
    
    result.push_back(node->id);
    
    for (int i = 1; i < node->children.size(); i++) {
        inOrder(node->children[i], result);
    }
}

// Duyệt theo thứ tự sau
void postOrder(Node* node, vector<int>& result) {
    if (node == NULL) return;
    
    for (Node* child : node->children) {
        postOrder(child, result);
    }
    
    result.push_back(node->id);
}

// In kết quả
void printResult(const vector<int>& result) {
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << " ";
    }
    cout << endl;
}

int main() {
    string command;
    
    while (cin >> command) {
        if (command == "*") break;
        
        if (command == "MakeRoot") {
            int u;
            cin >> u;
            makeRoot(u);
        }
        else if (command == "Insert") {
            int u, v;
            cin >> u >> v;
            insertNode(u, v);
        }
        else if (command == "PreOrder") {
            vector<int> result;
            preOrder(root, result);
            printResult(result);
        }
        else if (command == "InOrder") {
            vector<int> result;
            inOrder(root, result);
            printResult(result);
        }
        else if (command == "PostOrder") {
            vector<int> result;
            postOrder(root, result);
            printResult(result);
        }
    }
    
    return 0;
}