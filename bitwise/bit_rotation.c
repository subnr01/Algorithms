
// Rotate an integer n left by k
int rotLeft32(int n, int k)
{
  return (n << k) | ((unsigned int)n >> (32 - k));
}