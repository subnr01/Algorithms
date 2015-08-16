#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    int n;
    cout<<endl<< "Enter the number"<<endl;
    cin>>n;
    int a[10][10];
    int i;
    int sum1;
    int sum2;
    int final_sum;

    /* Calculate the diagonal sum left to right */
    cout<<endl<<"enter the matrix elements";
    int j;
    
    for (i = 0; i < n ; i++) {
        for (j = 0; j < n; j++) {
            cin>>a[i][j];
        }
    }
    
    for ( i = 0; i < n; i++) {
        sum1 += a[i][i];
    }
       
    /* Calculate the diagonal sum for right to left */
    
    for (i = n-1; i >=0 ; i--) {
        sum2+=a[i][n-1-i];
    }

    cout<<sum1;
    cout<<sum2;
    final_sum = sum1 - sum2;
    
    final_sum = final_sum < 0? final_sum * -1: final_sum;
    cout<<final_sum;
    return 0;
    
}
