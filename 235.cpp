/*************************************************************************
	> File Name: 235.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年07月07日 星期日 11时12分15秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>

#define MAX 10 
int arr[MAX + 5];

using namespace std;

void func(int k,int ind,int n,int *arr){
//k 
    if(k != 0){
        for (int i = 0;i<k;i++){
            i == 0 || cout << " " ;
            cout << arr[i] ;
        }
        cout << endl ;
    }
    for(int i = ind; i <= n; i++){
        arr[k] = i ;
        func(k + 1,i + 1, n, arr);
    }
    return ;
}

int main(){
    int n ;
    cin >> n ;
    func(0, 1, n, arr);
    return 0 ;
}
