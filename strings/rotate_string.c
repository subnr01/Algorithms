/*

Rotate a one-dimensional array of n elements to the right by k steps. 
For instance, with n=7 and k=3, the array {a, b, c, d, e, f, g} 
is rotated to {e, f, g, a, b, c, d}.

*/



void reverse_string(char* str, int left, int right) {
  char* p1 = str + left;
  char* p2 = str + right;
  while (p1 < p2) {
    char temp = *p1;
    *p1 = *p2;
    *p2 = temp;
    p1++;
    p2--;
  }
}
 
void rotate(char* str, int k) {
  int n = strlen(str);
  reverse_string(str, 0, n-1);
  reverse_string(str, 0, k-1);
  reverse_string(str, k, n-1);
}