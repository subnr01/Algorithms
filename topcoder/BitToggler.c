/*
Risa has n bits. The bits have indices from 0 to n-1, inclusive. She loves toggling the bits at random. (Toggling a bit means switching its value to the opposite one: from 0 to 1 or vice versa.)

Risa repeats a simple procedure when toggling the bits: If all bits have the same value, she is done. Otherwise, she selects a bit uniformly at random and toggles it.

Risa uses a cursor to toggle the bits. If the cursor is currently on bit i and Risa wants to toggle bit j next, she must move the cursor to bit j before she can toggle it. Each step of the cursor takes 1 unit of time. Therefore, moving the cursor from bit i to bit j takes |i-j| units of time. After Risa moves the cursor, she can toggle the bit instantly (in 0 units of time).

You will be given multiple queries. In each query we tell you the current state of Risa's bits and the current position of the cursor. Your task is to compute the expected time until the moment when all bits have the same value and Risa stops toggling them.

You will be given the int n. You will also be given a String[] bits and a int[] pos with Q elements each. For each valid i, the String bits[i] and the int pos[i] form one query. The characters of bits[i] give you the current values of all bits: bits[i][j] is '0'/'1' if bit j is 0/1. The int pos[i] is the current position of the cursor.

Return a double[] containing exactly Q elements. For each i, element i of the return value must be the expected time for the query (bits[i],pos[i]).
 
Definition
    	
Class:	BitToggler
Method:	expectation
Parameters:	int, String[], int[]
Returns:	double[]
Method signature:	double[] expectation(int n, String[] bits, int[] pos)
(be sure your method is public)
    
 
Notes
-	Each element of your return value must have absolute or relative error smaller than 1e-9.
 
Constraints
-	n will be between 1 and 20, inclusive.
-	bits and pos will contain between 1 and 1000 elements, inclusive.
-	bits and pos will contain the same number of elements.
-	Each element of bits will contain exactly n characters.
-	Each element of bits will only contain the characters '0' and '1'.
-	Each element of pos will be between 0 and n-1, inclusive.
 
Examples
0)	
    	
1
{"0","1"}
{0,0}
Returns: {0.0, 0.0 }
In each query, there is only one bit, therefore all bits have the same value and Risa doesn't do anything at all
1)	
    	
2
{"01"}
{0}
Returns: {0.5 }
If Risa choses bit 0, she will toggle it instantly and the process terminates (both bits are now 1).

If she chooses bit 1, she will spend 1 unit of time moving the cursor to this bit. Then she will toggle it and the process terminates (both bits are now 0).

As both possibilities are equally likely, the expected amount of time until the toggling terminates is 0.5.

2)	
    	
4
{"1000","0010","0011","1010"}
{0,1,2,3}
Returns: {8.9375, 8.5625, 9.75, 10.25 }
3)	
    	
20
{"01101111001001001111","01011100001001010111","00000000000000010000","10111111101111111011"
,"11101111111011010100","11111010110000000001","11000000100001100110","11111001010011101100"
,"11111111111111110111","01000011100010001000","01101111110111011111","11110111111111111110"
,"11111111111010110111","00100010000010000010","01000000000010000000","01110011111011000010"
,"11111101110001110111","11010010000000100000","10010101100000101000"}
{7,6,1,1,7,9,0,8,16,16,14,4,9,8,11,3,12,15,11}
Returns: 
{3695311.183337145, 3695341.038888902, 3486510.5078947134, 3690384.721723784, 3695146.5166465323, 3695333.788886834, 3695264.399989025, 3695310.983335239, 3486508.9763158862, 3695148.3166833473, 3693970.9054913437, 3670001.842105858, 3690381.122961273, 3693970.005510611, 3670000.4482457424, 3695335.888887129, 3694859.0889757653, 3694860.2888290025, 3695260.0000010678 
}


*/


#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 
class BitToggler {
public:
  vector <double> expectation(int, vector <string>, vector <int>);
};
 
long double a[42][42];
long double ans[42];
 
vector <double> BitToggler::expectation(int n, vector <string> bits, vector <int> pos) {
  long double value = (n - 1.0 / n) / 3.0;
  for (int i = 1; i <= n - 1; i++) {
    for (int j = 1; j <= n; j++) {
      a[i][j] = 0.0;
    }
  }
  for (int i = 1; i <= n - 1; i++) {
    if (i - 1 > 0) {
      a[i][i - 1] -= 1.0 * i / n;
    }
    if (i + 1 < n) {
      a[i][i + 1] -= 1.0 * (n - i) / n;
    }
    a[i][i] += 1.0;
    a[i][n] = value;
  }
  for (int e = 1; e <= n - 1; e++) {
    for (int i = 1; i <= n - 1; i++) {
      if (i == e) {
        continue;
      }
      long double coeff = -a[i][e] / a[e][e];
      for (int j = 1; j <= n; j++) {
        a[i][j] += coeff * a[e][j];
      }
    }
  }
  for (int i = 1; i <= n - 1; i++) {
    ans[i] = a[i][n] / a[i][i];
  }
  vector <double> ret;
  for (int z = 0; z < (int)bits.size(); z++) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
      if (bits[z][i] == bits[z][pos[z]]) {
        cnt++;
      }
    }
    if (cnt == 0 || cnt == n) {
      ret.push_back(0.0);
    } else {
      ret.push_back(ans[cnt]);
    }
  }
  return ret;
}
 
