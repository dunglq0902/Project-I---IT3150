#include <iostream>
#include <string>
#include <vector>
using namespace std;

int n;
int arr[25];

void backtrack(int pos){
    if(pos == n){
        for(int i=0; i<n; i++){
            cout<<arr[i];
        }
        cout<<endl;
        return;
    }

    arr[pos] = 0;
    //gán 0 từ vị trí đầu, rồi đệ quy gán 0 lần lượt
    backtrack(pos+1);
    //khi đến vị trí cuối thì in ra mảng full 0 đầu 
    
    if(pos ==0 || arr[pos-1] == 0){
        arr[pos] = 1;
        backtrack(pos+1);
    }

}
int main(){
    cin>>n;
    backtrack(0);
    return 0;    
}
//Given an integer n, write a program that generates all binary sequences without consecutive 11 in a lexicographic order.
