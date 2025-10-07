#include<iostream>
#include<string>
using namespace std;

struct Node{
    int data;
    Node*next;
    Node(int val):data(val), next(NULL){}
};

bool exists(Node* head, int key){
    Node* current = head;
    while(current != NULL){
        if(current->data == key)
            return true;

        //Nếu không tìm thấy thì tiếp tục duyệt
        current = current->next;
    }
    return false;
}

//Thêm vào cuối
void addLast(Node*& head, int key){//Node*& head: Tham chiếu đến một con trỏ head
    if(exists(head, key))
        return;

    Node* newNode = new Node(key);
    if(head == NULL){
        head = newNode;
        return;
    }

    Node* current = head; //Con trỏ current đang trỏ đến vị trí đầu tiên của danh sách
    while(current->next != NULL){
        current = current->next;
    }
    current->next = newNode;
}

//Thêm vào đầu
void addFirst(Node*& head, int key){
    if(exists(head, key))   
        return;
    Node* newNode = new Node(key);
    newNode->next = head;
    head = newNode;
}

//Thêm u vào sau v
void addAfter(Node* head, int u, int v){
    if(exists(head, u) || !exists(head, v))
        return;
    
    Node* current = head;
    while(current != NULL){
        if(current->data ==v){
            Node* newNode = new Node(u);
            newNode->next = current->next;
            current->next = newNode;
            return;
        }
        current = current->next;
    }
}

// Thêm u vào trước v
void addBefore(Node*& head, int u, int v){
    if(exists(head, u) || !exists(head, v))
        return;
    
    if(head->data == v){
        addFirst(head, u);
        return;
    }

    Node* current = head;
    while(current->next != NULL){
        if(current->next->data == v){
            Node* newNode = new Node(u);
            newNode->next = current->next;
            current->next = newNode;
            return;
        }
        current = current->next;
    }
}

//Xóa phần tử
void remove(Node*& head, int key){
    if(head == NULL)
        return;
    
    if(head->data == key){
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
    while(current->next != NULL){
        if(current->next->data == key){
            Node*temp = current->next;
            current->next = current->next->next;
            delete temp;
            return;
        }
        current = current->next;
    }
}

// Đảo ngược danh sách
void reverse(Node*& head) {
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;
    
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

// In danh sách
void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data;
        if (current->next != nullptr) cout << " ";
        current = current->next;
    }
    cout << endl;
}

int main(){
    Node* head = NULL;
    int n, val;

    cin>>n;
    for(int i=0; i<n; i++){
        cin>>val;
        addLast(head, val);
    }

    string command;
    while(cin>>command){
        if(command == "#") 
            break;

        if(command == "addlast"){
            cin>>val;
            addLast(head, val);
        }
        else if(command == "addfirst"){
            cin>>val;
            addFirst(head, val);
        }
        else if(command == "addafter"){
            int u, v;
            cin>>u>>v;
            addAfter(head, u, v);
        }
        else if(command == "addbefore"){
            int u, v;
            cin>>u>>v;
            addBefore(head, u, v);
        }
        else if(command == "remove"){
            cin>>val;
            remove(head, val);
        }
        else if(command == "reverse"){
            reverse(head);
        }
    }
    printList(head);
    return 0;
}