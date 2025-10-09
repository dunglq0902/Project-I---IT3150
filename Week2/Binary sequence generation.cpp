#include<iostream>
using namespace std;
int n;
int arr[100]={0};
void biSequence(int index){
    if(index == n)
    {
        for(int i=0; i<n; i++)
            cout<< arr[i];
        cout<<endl;
        return;
    }
    arr[index] = 0;
    biSequence(index+1);
    arr[index] = 1;
    biSequence(index+1);


}
int main()
{
    cin>>n;
    biSequence(0);
    return 0;
}
