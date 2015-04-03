
/*

Print string in reverse order

*/

void printReverse(const char *str) {
  if (!*str)
    return;
  printReverse(str + 1);
  putchar(*str);
}


/* print unsigned long without using itoa */

void putlong(unsigned long n) {
  if (n == 0)
    return;
  putlong(n / 10);
  putchar(n % 10 + '0');
}
