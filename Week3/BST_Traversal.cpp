#include <iostream>
#include <string>
using namespace std;

struct Node{
    int key;
    Node *left;
    Node *right;

    Node(int k): key(k), left(NULL), right(NULL){}
};

// Hàm chèn key vào BST
Node* insert(Node* root, int key){
    if(root == NULL)
        return new Node(key);
    if(root->key == key)
        return root;
    if(key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    return root;
}

// Hàm duyệt pre-order
void preOrder(Node* root){
    if(root != NULL){
        cout <<root->key<<" ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Hàm giải phóng bộ nhớ
void clearTree(Node* root) {
    if (root != nullptr) {
        clearTree(root->left);
        clearTree(root->right);
        delete root;
    }
}

int main(){
    Node *root = NULL;
    string line;

    while(cin>>line){
        if(line == "#"){
            break;
        }
        if(line == "insert"){
            int key;
            cin>>key;
            root = insert(root, key);
        }
    }
    preOrder(root);

        // Giải phóng bộ nhớ
    clearTree(root);

}