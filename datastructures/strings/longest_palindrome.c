
/*

Given a string S, find the longest palindromic substring in S.

*/

/*

Solution

Brute force solution, O(N3): 

The obvious brute force solution is to pick all
possible starting and ending positions for a substring, and verify if it is a
palindrome. There are a total of C(N, 2) such substrings (excluding the trivial
solution where a character itself is a palindrome).

Since verifying each substring takes O(N) time, the run time complexity is O(N3).

Dynamic programming solution, O(N2) time and O(N2) space: 

To improve over the
brute force solution from a DP approach, first think how we can avoid
unnecessary re-computation in validating palindromes. Consider the case “ababa”.
If we already knew that “bab” is a palindrome, it is obvious that “ababa” must
be a palindrome since the two left and right end letters are the same.


Stated more formally below:

Define P[ i, j ] ← true iff the substring Si … Sj is a palindrome, otherwise false.
Therefore,

P[ i, j ] ← ( P[ i+1, j-1 ] and Si = Sj )
The base cases are:

P[ i, i ] ← true
P[ i, i+1 ] ← ( Si = Si+1 )
This yields a straight forward DP solution, which we first initialize the one and two 
letters palindromes, and work our way up finding all three letters palindromes, and so on… 

This gives us a run time complexity of O(N2) and uses O(N2) space to store the table.

*/

string longestPalindromeDP(string s) {
  int n = s.length();
  int longestBegin = 0;
  int maxLen = 1;
  bool table[1000][1000] = {false};
  for (int i = 0; i < n; i++) {
    table[i][i] = true;
  }
  for (int i = 0; i < n-1; i++) {
    if (s[i] == s[i+1]) {
      table[i][i+1] = true;
      longestBegin = i;
      maxLen = 2;
    }
  }
  for (int len = 3; len <= n; len++) {
    for (int i = 0; i < n-len+1; i++) {
      int j = i+len-1;
      if (s[i] == s[j] && table[i+1][j-1]) {
        table[i][j] = true;
        longestBegin = i;
        maxLen = len;
      }
    }
  }
  return s.substr(longestBegin, maxLen);
}



/*

A simpler approach, O(N2) time and O(1) space: In fact, we could solve it in
O(N2) time without any extra space.

We observe that a palindrome mirrors around its center. Therefore, a palindrome
can be expanded from its center, and there are only 2N-1 such centers.

You might be asking why there are 2N-1 but not N centers? The reason is the
center of a palindrome can be in between two letters. Such palindromes have even
number of letters (such as “abba”) and its center are between the two ‘b’s.

Since expanding a palindrome around its center could take O(N) time, the overall
complexity is O(N2).

*/

string expandAroundCenter(string s, int c1, int c2) {
  int l = c1, r = c2;
  int n = s.length();
  while (l >= 0 && r <= n-1 && s[l] == s[r]) {
    l--;
    r++;
  }
  return s.substr(l+1, r-l-1);
}
 
string longestPalindromeSimple(string s) {
  int n = s.length();
  if (n == 0) return "";
  string longest = s.substr(0, 1);  // a single char itself is a palindrome
  for (int i = 0; i < n-1; i++) {
    string p1 = expandAroundCenter(s, i, i);
    if (p1.length() > longest.length())
      longest = p1;
 
    string p2 = expandAroundCenter(s, i, i+1);
    if (p2.length() > longest.length())
      longest = p2;
  }
  return longest;
}


/*
This is a complex algorithm, so they may not expect this in
interview.

Here, we describe an algorithm (Manacher’s algorithm) which finds 
the longest palindromic substring in linear time.

Here, we discuss an algorithm that runs in O(N) time and O(N) space,
 also known as Manacher’s algorithm.

Think how you would improve over the simpler O(N2) approach. Consider the worst
case scenarios. The worst case scenarios are the inputs with multiple
palindromes overlapping each other. For example, the inputs: “aaaaaaaaa” and
“cabcbabcbabcba”. In fact, we could take advantage of the palindrome’s symmetric
property and avoid some of the unnecessary computations.

An O(N) Solution (Manacher’s Algorithm): First, we transform the input string,
S, to another string T by inserting a special character ‘#’ in between letters.
The reason for doing so will be immediately clear to you soon.

For example: S = “abaaba”, T = “#a#b#a#a#b#a#”.

To find the longest palindromic substring, we need to expand around each Ti such
that Ti-d … Ti+d forms a palindrome. You should immediately see that d is the
length of the palindrome itself centered at Ti.

We store intermediate result in an array P, where P[ i ] equals to the length of
the palindrome centers at Ti. The longest palindromic substring would then be
the maximum element in P.

Using the above example, we populate P as below (from left to right):

T = # a # b # a # a # b # a # P = 0 1 0 3 0 1 6 1 0 3 0 1 0 Looking at P, we
immediately see that the longest palindrome is “abaaba”, as indicated by P6 = 6.

Did you notice by inserting special characters (#) in between letters, both
palindromes of odd and even lengths are handled graciously? (Please note: This
is to demonstrate the idea more easily and is not necessarily needed to code the
algorithm.)

Now, imagine that you draw an imaginary vertical line at the center of the
palindrome “abaaba”. Did you notice the numbers in P are symmetric around this
center? That’s not only it, try another palindrome “aba”, the numbers also
reflect similar symmetric property. Is this a coincidence? The answer is yes and
no. This is only true subjected to a condition, but anyway, we have great
progress, since we can eliminate recomputing part of P[ i ]‘s.

Let’s summarize the key part of this algorithm as below:


if P[ i' ] ≤ R – i, 
then P[ i ] ← P[ i' ] 
else P[ i ] ≥ P[ i' ]. 
(Which we have
to expand past the right edge (R) to 
find P[ i ].)




See how elegant it is? If you are able to grasp the above summary fully, you
already obtained the essence of this algorithm, which is also the hardest part.

The final part is to determine when should we move the position of C together
with R to the right, which is easy:

If the palindrome centered at i does expand past R, we update C to i, (the
center of this new palindrome), and extend R to the new palindrome’s right edge.
In each step, there are two possibilities. If P[ i ] ≤ R – i, we set P[ i ] to
P[ i' ] which takes exactly one step. Otherwise we attempt to change the
palindrome’s center to i by expanding it starting at the right edge, R.
Extending R (the inner while loop) takes at most a total of N steps, and
positioning and testing each centers take a total of N steps too. Therefore,
this algorithm guarantees to finish in at most 2*N steps, giving a linear time
solution.
*/

// Transform S into T.
// For example, S = "abba", T = "^#a#b#b#a#$".
// ^ and $ signs are sentinels appended to each end to avoid bounds checking
string preProcess(string s) {
  int n = s.length();
  if (n == 0) return "^$";
  string ret = "^";
  for (int i = 0; i < n; i++)
    ret += "#" + s.substr(i, 1);
 
  ret += "#$";
  return ret;
}
 
string longestPalindrome(string s) {
  string T = preProcess(s);
  int n = T.length();
  int *P = new int[n];
  int C = 0, R = 0;
  for (int i = 1; i < n-1; i++) {
    int i_mirror = 2*C-i; // equals to i' = C - (i-C)
    
    P[i] = (R > i) ? min(R-i, P[i_mirror]) : 0;
    
    // Attempt to expand palindrome centered at i
    while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
      P[i]++;
 
    // If palindrome centered at i expand past R,
    // adjust center based on expanded palindrome.
    if (i + P[i] > R) {
      C = i;
      R = i + P[i];
    }
  }
 
  // Find the maximum element in P.
  int maxLen = 0;
  int centerIndex = 0;
  for (int i = 1; i < n-1; i++) {
    if (P[i] > maxLen) {
      maxLen = P[i];
      centerIndex = i;
    }
  }
  delete[] P;
  
  return s.substr((centerIndex - 1 - maxLen)/2, maxLen);
}