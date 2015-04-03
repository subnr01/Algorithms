/*

Given a string of lowercase characters, reorder them such 
that the same characters are at least distance d from each other.

Input: { a, b, b }, distance = 2
Output: { b, a, b }

*/


int find_max(int freq[], bool excep[]) {
  int max_i = -1;
  int max = -1;
  for (char c = 'a'; c <= 'z'; c++) {
    if (!excep[c] && freq[c] > 0 && freq[c] > max) {
      max = freq[c];
      max_i = c;
    }
  }
  return max_i;
}
 
void create(char* str, int d, char ans[]) {
  int n = strlen(str);
  int freq[256] = {0};
  for (int i = 0; i < n; i++)
  freq[str[i]]++;
 
  int used[256] = {0};
  for (int i = 0; i < n; i++) {
  bool excep[256] = {false};
  bool done = false;
  while (!done) {
    int j = find_max(freq, excep);
    if (j == -1) {
      cout << "Error!\n";
      return;
    }
    excep[j] = true;
    if (used[j] <= 0) {
      ans[i] = j;
      freq[j]--;
      used[j] = d;
      done = true;
    } 
  }
  for (int i = 0; i < 256; i++)
    used[i]--;
  }
  ans[n] = '\0';
}