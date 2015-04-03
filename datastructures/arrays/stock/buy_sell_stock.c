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




========================================
/*
The cost of a stock on each day is given in an array, find the max profit that you can make by buying and selling in those days. For example, if the given array is {100, 180, 260, 310, 40, 535, 695}, the maximum profit can earned by buying on day 0, selling on day 3. Again buy on day 4 and sell on day 6. If the given array of prices is sorted in decreasing order, then profit cannot be earned at all.
If we are allowed to buy and sell only once, then we can use following algorithm. Maximum difference between two elements. Here we are allowed to buy and sell multiple times. Following is algorithm for this problem.
1. Find the local minima and store it as starting index. If not exists, return.
2. Find the local maxima. and store it as ending index. If we reach the end, set the end as ending index.
3. Update the solution (Increment count of buy sell pairs)
4. Repeat the above steps if end is not reached.
// This function finds the buy sell schedule for maximum profit

*/


void stockBuySell(int price[], int n)
{
    // Prices must be given for at least two days
    if (n == 1)
        return;
 
    int count = 0; // count of solution pairs
 
    // solution vector
    Interval sol[n/2 + 1];
 
    // Traverse through given price array
    int i = 0;
    while (i < n-1)
    {
        // Find Local Minima. Note that the limit is (n-2) as we are
        // comparing present element to the next element. 
        while ((i < n-1) && (price[i+1] <= price[i]))
            i++;
 
        // If we reached the end, break as no further solution possible
        if (i == n-1)
            break;
 
        // Store the index of minima
        sol[count].buy = i++;
 
        // Find Local Maxima.  Note that the limit is (n-1) as we are
        // comparing to previous element
        while ((i < n) && (price[i] >= price[i-1]))
            i++;
 
        // Store the index of maxima
        sol[count].sell = i-1;
 
        // Increment count of buy/sell pairs
        count++;
    }
 
    // print solution
    if (count == 0)
        printf("There is no day when buying the stock will make profit\n");
    else
    {
       for (int i = 0; i < count; i++)
          printf("Buy on day: %d\t Sell on day: %d\n", sol[i].buy, sol[i].sell);
    }
 
    return;
}
/*
http://stackoverflow.com/questions/7086464/maximum-single-sell-profit
http://stackoverflow.com/questions/9514191/maximizing-profit-for-given-stock-quotes
http://stackoverflow.com/questions/1663545/find-buy-sell-prices-in-array-of-stock-values-to-maximize-positive-difference
*/
