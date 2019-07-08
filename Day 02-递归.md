# Day 02

## 递归程序设计

> 一种技巧，程序调用自身

1. 定义一个明确的语义信息
2.  确定边界条件
3.  针对于问题的`处理过程` 和`递归过程`
4.  结果返回

> 随堂练习 1

``` c++
//6.func.cpp
//计算N阶乘
#include<iostream>
using namespace std ;

int f(int n){//定义函数
    if(n<=1) return 1 ;//0和1的阶乘均为1
    return n*f(n-1) ;//若n！=0||1，则需要递归
}

int main(void){
    int n ;
    cin >> n ;
    cout << f(n) <<endl ;//由于返回值就是最终结果，因此直接cout
    return 0 ;
}
```



## 辗转相除法

1. 用于快速计算两个数字的最大公约数

2. 用于快速求解 **`a*x + b*y = 1`** 的一组整数解

   ```
   证明过程：
   gcd(a,b) = gcd(b,a%b)
   a = x*d && b = y*d 
   gcd(x,y) = 1
   a%b = a - k*b = x*b - k*y*d = (x-k*y)*d
   ```

3. 求解 `a*x + b*y = 1` 的分析

   ```
   a*x + b*y = 1
   b*x + (a-k*b)*y = 1
   a*y + b*(x-ky) = 1 
   ```

4. 使用辗转辗转相除法求解方程的具体算法实现

   ```c++
   //7.gcd.cpp
   #include<iostream>
   #include<stdio.h>
   using namespace std;
   
   int gcd(int a, int b){
       if(b == 0) return 0 ;
       return gcd(b, a % b);
       //return (b ? gcd(b, a % b): a);
   }
   
   int ex_gcd(int a,int b,int &x,int &y){
       //&x,&y x,y的引用， 希望传出结果
       if(b == 0){
           x = 1; y = 0;
           return a ;
       }
       int r = ex_gcd(b , a%b, y , x);
       //假设有两个变量sx，sy(表示当前的X和Y的值)
       //x = sy ；y = sx + a/b * sy
       //从而将ex_gcd()中的参数确定
       y -= a/b * x ;
       return r ;
   }
   
   int main(void){
       int a,b ;
       while (cin >>a>>b){
           int x,y,r ;
           r = ex_gcd(a,b,x,y) ;
           cout << "rest :"<< r << endl ;
           printf("%d * %d + %d * %d = %d\n", a, x, b, y, a * x + b * y );
       }
       return 0 ;
   }
   ```

   

## 递归指数枚举

1. 问题描述：

   ![](/home/young/图片/递归1-指数型.png)



2. 源代码展示：

``` c++
//235.cpp
#include<iostream>
#include<stdio.h>

#define MAX 10 
int arr[MAX + 5];//存放最终结果的数组

using namespace std;

void func(int k,int ind,int n,int *arr){
//k表示当前所在节点，ind表示当前可以操作的最小的数，n表示当前可以操作的最大的数，*arr指向存储数组
    if(k != 0){//如果当前节点不是根节点
        for (int i = 0;i<k;i++){
            i == 0 || cout << " " ;
            cout << arr[i] ;
        }
        cout << endl ;
    }
    for(int i = ind; i <= n; i++){
        arr[k] = i ;
        func(k + 1,i + 1, n, arr);
    }//从根节点开始向下遍历，每一层遍历结束，就向下一层继续遍历
    return ;
}

int main(){
    int n ;
    cin >> n ;
    func(0, 1, n, arr);
    return 0 ;
}
```



## 递归组合型枚举

1. 问题描述：

![](/home/young/图片/递归1-组合型.png)

2. 源代码展示：

```c++
//236.cpp
#include<iostream>
#define Max 10

int arr[Max + 5] ;

using namespace std;

void func(int k ,int m,int ind ,int n,int *arr){
    //ind表示当前可以操作(输出)的最小的数
    //k 用来控制输出
    if(k == m){
        for(int i = 0;i<m;i++){
            i == 0 || cout << " " ;
            cout << arr[i] ;
        }
        cout << endl ;
        return ;
    }
    for(int i = ind ;i<=n; i++){
        arr[k] = i ;
        func(k+1, m, i+1, n, arr);
    }//递归主体
    return ;
}



int main(){
    int n, m ;
    cin >> n >> m ;
    func(0, m ,1, n, arr) ;
    return 0 ;
}
```



## 表达式计算

1. 问题描述：

![](/home/young/图片/递归1-表达式.png)

2. 问题分析：

[^表达式树]: 

![](/home/young/图片/表达式树1.png)

![](/home/young/图片/表达式树2.png)

3. 源代码展示：

```c++
//266.cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
using namespace std;
#define INF 0x3f3f3f3f

int calc(char *str, int l, int r) {
    int pos = -1, pri = INF, temp = 0;
    for (int i = l; i < r; i++) {
        int cur_pri = INF + 1;
        switch (str[i]) {
            case '(': temp += 100; break;
            case ')': temp -= 100; break;
            case '+': 
            case '-': cur_pri = temp + 1; break;
            case '*':
            case '/': cur_pri = temp + 2; break;
            case '^': cur_pri = temp + 3; break;
        }
        if (cur_pri <= pri) {
            pos = i;
            pri = cur_pri;
        }
    }
    if (pos == -1) {
        int num = 0;
        for (int i = l; i < r; i++) {
            if (str[i] < '0' || str[i] > '9') continue;
            num = num * 10 + str[i] - '0';
        }
        return num;
    }
    int a = calc(str, l, pos);
    int b = calc(str, pos + 1, r);
    switch (str[pos]) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return (int)pow(a, b);
    }
    return 0;
}

int main() {
    char str[1000];
    while (cin >> str) {
        cout << calc(str, 0, strlen(str)) << endl;
    }
    return 0;
}
```

