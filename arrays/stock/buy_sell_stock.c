/*

Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to buy one share of the stock and sell one share of the stock, 
design an algorithm to find the best times to buy and sell.

*/



/*

The question is equivalent to the following:

Find i and j that maximizes Aj – Ai, where i < j.

*/


/*

To solve this problem efficiently, you would need to track the minimum value’s
index. As you traverse, update the minimum value’s index when a new minimum is
met. Then, compare the difference of the current element with the minimum value.
Save the buy and sell time when the difference exceeds our maximum difference
(also update the maximum difference).

*/

void getBestTime(int stocks[], int sz, int &buy, int &sell) {
  int min = 0;
  int maxDiff = 0;
  buy = sell = 0;
  for (int i = 0; i < sz; i++) {
    if (stocks[i] < stocks[min])
      min = i;
    int diff = stocks[i] - stocks[min];
    if (diff > maxDiff) {
      buy = min;
      sell = i;
      maxDiff = diff;
    }
  }
}

