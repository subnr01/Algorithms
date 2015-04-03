/*

Given a target number, and a series of candidate numbers, print out all combinations, 
so that the sum of candidate numbers equals to the target.

Here order is not important, so don’t print the duplicated combination.

e.g. target is 7, candidate is 2,3,6,7
output should be 7 and 3+2+2 (but not print 2+3+2, 2+2+3)

*/


/* 
Solution 
First, we start with a sum of 0. Then, we iterate over all
possibilities that can be added to sum, which yields the possible set of
sum={2,3,6,7}. Assume now that sum=2, we continue adding all possible candidate
numbers {2,3,6,7} to sum=2, which yields sum={4,5,8,9}. Each step we have to use
an array to keep track of all the indices of candidate numbers that add to the
current sum, so that we can print the combination later. The next case would be
sum=3. We look at all possible candidate numbers {3,6,7} to be added to sum=3,
which yields sum={6,9,10}. Note that there is no need to look backward (ie,
candidate numbers that are smaller than 3), as this would only yield duplicate
results. We keep doing this recursively, until we reach the conditions below,
where we stop.


*/



void printSum(int candidates[], int index[], int n) {
  for (int i = 1; i <= n; i++)
    cout << candidates[index[i]] << ((i == n) ? "" : "+");
  cout << endl;
}
 
void solve(int target, int sum, int candidates[], int sz, int index[], int n) {
  if (sum > target)
    return;
  if (sum == target)
    printSum(candidates, index, n);
 
  for (int i = index[n]; i < sz; i++) {
    index[n+1] = i;
    solve(target, sum + candidates[i], candidates, sz, index, n+1);
  }
}
 
void solve(int target, int candidates[], int sz) {
  int index[10000];
  index[0] = 0;
  solve(target, 0, candidates, sz, index, 0);
}