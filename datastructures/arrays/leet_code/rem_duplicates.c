
class Solution {
public:
      int removeDuplicates(int A[], int n) {
          if (n == 0) return 0;
          int index = 0;
          for (int i = 1; i < n; i++) {
              if (A[index] != A[i])
                  A[++index] = A[i];
}
          return index + 1;
      }
};


//if duplicates are allowed twice
//

class Solution {
  public:
      int removeDuplicates(int A[], int n) {
          if (n <= 2) return n;
          int index = 2;
          for (int i = 2; i < n; i++){
              if (A[i] != A[index - 2])
                  A[index++] = A[i];
}
          return index;
      }
};
