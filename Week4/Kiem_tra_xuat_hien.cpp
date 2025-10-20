#include<iostream>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int array[n];

    for(int i= 0; i<n; i++){
        cin>>array[i];
    }
    for(int i = 0; i<n; i++){
        bool found = false;
        for(int j = 0; j<i; j++){   // ban đầu i = 0, j =0 có điều kiện j<i nên i=0,j=0 sẽ không chạy=> in ra 0 luôn
            if(array[j] == array[i]){
                found = true;
                break;
            }
        }
        if(found)
            cout<<1<<endl;
        else
            cout<<0<<endl;
    }
    return 0;
}