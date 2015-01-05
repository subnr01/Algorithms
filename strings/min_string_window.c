/*


Given a set T of characters and a string S, find the minimum window in S
 which will contain all the characters in T in complexity O(n).

eg,
S = “ADOBECODEBANC”
T = “ABC”

Minimum window is “BANC”.

*/

/* 

Using the above example S = “ADOBECODEBANC” and T = “ABC“, we can easily find
the first window which contains T is “ADOBEC“. Another possible candidate is
“ADOBECODEBA“. In fact, we should skip this, because within it exists a sub-
window “CODEBA” that is both shorter and satisfy the constraint. The final
window to consider is “BANC“, which is also the minimum window.

To solve this problem efficiently, below are the two key points we need to
consider:

How do we determine if a particular window contains T? (ideally in O(1) time)
How do we select all windows efficiently? (ideally do not include other windows that 
wrap about a sub-window)


We definitely need the help from a hash table here. Hash table is able to tell us if a 
letter exist in T in O(1) time.

*/

/*

An O(N lg M) solution:


When I first approach this problem, I thought of having another table which
records the position of last-met character in T. That is, when I first see ‘A‘,
I record its position being 0. Each time I see ‘A‘ again, I replace its position
with the new position. This approach is simple but flawed. Notice that T does
not include duplicate characters? If T includes duplicate characters, such as
“AABC“, this approach does not work.

In this case, the remedy is to maintain queues (instead of table) that
correspond to each unique character in T. For example, assume that T = “AABC“,
when you first see ‘A‘, push its position into the ‘A‘ queue (which originally
is empty). When you see ‘A‘ again, push its position to the back of ‘A‘ queue.
The third time you see ‘A‘, you would pop the front element, and push its
position to the back of ‘A‘ queue. By popping the element, we do not include
window that wrap around a sub-window. This approach works but the difficulty is
two-fold:

There is no way we could determine the starting and ending position of a window
directly from the queue itself. A naive way is to scan the entire queue for
minimum and maximum value. How do we determine if the window satisfies the
constraint? We would have to scan all queues to check if the sum of all queues’
sizes is equal to T‘s length. The way I solve the above problem is to maintain a
sorted map that maps indices to character so that we can grab the minimum and
maximum position in O(1) time. But there is an extra cost for doing this. Each
time you pop an element from the queue, you would also need to update the map by
deleting the corresponding element and inserting a new element. To check if the
window satisfies the constraint, we check the map’s size; a valid window is
found if the map’s size is equal to T’s length.

The complexity of the method is O(N lg M), where N is the length of S, and M is
the length of T. The extra lg M term is due to the extra cost of deleting and
inserting an element in the map, where each costs O(lg M) time in the worst case
(Note that M is the map’s maximum size. Why?)

*/


// Returns false if no valid window is found. Else returns 
// true and updates minWindowBegin and minWindowEnd with the 
// starting and ending position of the minimum window.
bool findMinWindow(const char *str, const char *pattern, 
                   int &minWindowBegin, int &minWindowEnd) {
  int N = strlen(str);
  int M = strlen(pattern);
  int minWindowLen = INT_MAX;
   
  // hash table init all to 0s
  // used to check how many letters left in T to be filled
  int needToFill[256] = {0};
 
  for (int i = 0; i < M; i++)
    needToFill[pattern[i]]++;
 
  // set the rest to -1 so we know that letter is not in T
  for (int i = 0; i < 256; i++)
    if (needToFill[i] == 0)
      needToFill[i] = -1;
 
  // array of queues, each corresponds to a unique char in T
  queue<int> q[256];
 
  // maintains a sorted map (maps indices to char), 
  // the first and last element tells us the 
  // starting and ending position of the window
  map<int,char> m;
 
  for (int i = 0; i < N; i++) {
    // skips characters not in T
    if (needToFill[str[i]] == -1) continue;
    
    // push character to queue
    if (q[str[i]].size() < needToFill[str[i]]) {
      q[str[i]].push(i);
      m[i] = str[i];
    }
    // replace the character in the queue 
    // and updates the corresponding element in the map
    else {
      int idxToErase = q[str[i]].front();
      map<int,char>::iterator it = m.find(idxToErase);
      m.erase(it);
      m[i] = str[i];
      q[str[i]].pop();
      q[str[i]].push(i);
    }
 
    // found a window, check for minimum
    if (m.size() == M) {
      int end = m.rbegin()->first;
      int begin = m.begin()->first;
      int windowLen = end - begin + 1;
      if (windowLen < minWindowLen) {
        minWindowLen = windowLen;
        minWindowBegin = begin;
        minWindowEnd = end;
      }
    } // end if
  } // end for
   
  return (m.size() == M) ? true : false;
}



/* 

Best solution



Notice how complicated the above solution is. It uses a hash table, a queue, and
a sorted map. During an interview, the problems tend to be short and the
solution usually can be coded in about 50 lines of code. So be sure that you say
out loud what you are thinking and keep communication opened with the
interviewer. Check if your approach is unnecessary complex, he/she might be able
to give you guidance. The last thing you want to do is to get stuck in a corner
and keep silent.

To help illustrate this approach, I use a different example: S = “acbbaca” and T
= “aba“. The idea is mainly based on the help of two pointers (begin and end
position of the window) and two tables (needToFind and hasFound) while
traversing S. needToFind stores the total count of a character in T and hasFound
stores the total count of a character met so far. We also use a count variable
to store the total characters in T that’s met so far (not counting characters
where hasFound[x] exceeds needToFind[x]). When count equals T‘s length, we know
a valid window is found.

Each time we advance the end pointer (pointing to an element x), we increment
hasFound[x] by one. We also increment count by one if hasFound[x] is less than
or equal to needToFind[x]. Why? When the constraint is met (that is, count
equals to T‘s size), we immediately advance begin pointer as far right as
possible while maintaining the constraint.

How do we check if it is maintaining the constraint? Assume that begin points to
an element x, we check if hasFound[x] is greater than needToFind[x]. If it is,
we can decrement hasFound[x] by one and advancing begin pointer without breaking
the constraint. On the other hand, if it is not, we stop immediately as
advancing begin pointer breaks the window constraint.

Finally, we check if the minimum window length is less than the current minimum.
Update the current minimum if a new minimum is found.

Essentially, the algorithm finds the first window that satisfies the constraint,
then continue maintaining the constraint throughout.

*/



// Returns false if no valid window is found. Else returns 
// true and updates minWindowBegin and minWindowEnd with the 
// starting and ending position of the minimum window.
bool minWindow(const char* S, const char *T, 
               int &minWindowBegin, int &minWindowEnd) {
  int sLen = strlen(S);
  int tLen = strlen(T);
  int needToFind[256] = {0};
 
  for (int i = 0; i < tLen; i++)
    needToFind[T[i]]++;
 
  int hasFound[256] = {0};
  int minWindowLen = INT_MAX;
  int count = 0;
  for (int begin = 0, end = 0; end < sLen; end++) {
    // skip characters not in T
    if (needToFind[S[end]] == 0) continue;
    hasFound[S[end]]++;
    if (hasFound[S[end]] <= needToFind[S[end]])
      count++;
 
    // if window constraint is satisfied
    if (count == tLen) {
      // advance begin index as far right as possible,
      // stop when advancing breaks window constraint.
      while (needToFind[S[begin]] == 0 ||
            hasFound[S[begin]] > needToFind[S[begin]]) {
        if (hasFound[S[begin]] > needToFind[S[begin]])
          hasFound[S[begin]]--;
        begin++;
      }
 
      // update minWindow if a minimum length is met
      int windowLen = end - begin + 1;
      if (windowLen < minWindowLen) {
        minWindowBegin = begin;
        minWindowEnd = end;
        minWindowLen = windowLen;
      } // end if
    } // end if
  } // end for
 
  return (count == tLen) ? true : false;
}

/* Both the begin and end pointers can advance at most N steps (where N is S‘s
size) in the worst case, adding to a total of 2N times. Therefore, the run time
complexity must be in O(N). */
