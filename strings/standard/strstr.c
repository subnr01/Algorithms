/*

Write C code to implement the strstr (Search for a substring) function. 
Do not use any system library such as strlen.



/*

The strstr function locates a specified substring within a source string. Strstr
returns a pointer to the first occurrence of the substring in the source. If the
substring is not found, strstr returns a null pointer.

As expected, this question is very popular among technical interviews. This
question tests your ability in manipulating strings using pointers, as well as
your coding ability.

Of course, you can demonstrate to your interviewer that this problem can be
solved using known efficient algorithms such as Rabin-Karp algorithm, KMP
algorithm, and the Boyer-Moore algorithm. Since these algorithms are usually
studied in advanced algorithms class, for an interview it is sufficient to solve
it using the most direct method — The brute force method.

The brute force method is straightforward to implement. We scan the substring
(the target) with the string from its first position and start matching all
subsequent letters one by one. If one of the letter doesn’t match, we start over
again with the next position in the string. Assume that N = length of string, M
= length of substring, then the complexity is O(N*M).

*/

char* StrStr(const char *str, const char *target) {
  if (!*target) return str;
  char *p1 = (char*)str;
  while (*p1) {
    char *p1Begin = p1, *p2 = (char*)target;
    while (*p1 && *p2 && *p1 == *p2) {
      p1++;
      p2++;
    }
    if (!*p2)
      return p1Begin;
    p1 = p1Begin + 1;
  }
  return NULL;
}




/*

Did you handle the special case correctly? That is, when the target substring is
an empty string. What should you return in this case? The correct implementation
of strstr should return the full string in this case.

The above solution is usually good enough for an interview. But it turns out we
are able to improve the code a little further. Note that the above code iterates
at most N times in the outer loop.

The improvement is based on one observation: We only need to iterate at most
N-M+1 times in the outer loop. Why? Because after looping more than N-M+1 times,
the string has less than M characters to be matched with the substring. In this
case, we know no more substring will be found in the string, and therefore
saving us from additional comparisons (which might be substantial especially
when M is large compared to N.)

How do we loop for only N-M+1 times? We are able to calculate the size of the
string and substring by iterating a total of N+M times. In fact, finding just
the length of the substring, M is sufficient. We use an additional pointer,
p1Adv and advance it M-1 times ahead of the string pointer. Therefore, when
p1Adv points to ‘\0′, we know that it has iterated N-M+1 times.


*/

char* StrStr(const char *str, const char *target) {
  if (!*target) return str;
  char *p1 = (char*)str, *p2 = (char*)target;
  char *p1Adv = (char*)str;
  while (*++p2)
    p1Adv++;
  while (*p1Adv) {
    char *p1Begin = p1;
    p2 = (char*)target;
    while (*p1 && *p2 && *p1 == *p2) {
      p1++;
      p2++;
    }
    if (!*p2)
      return p1Begin;
    p1 = p1Begin + 1;
    p1Adv++;
  }
  return NULL;
}