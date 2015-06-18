
/* Program to demonstrate bubble sort.
Order of the algorithm is n2


Outer loop selects the element.
Inner loop compares the element with all other positions in the array.
Inner loop selects the position of the element.
When a position is found, the elements are swapped.

*/

void bubble_sort (int *a, int n) {
    int i, t;
    bool swapped = 1;
    while (swapped) {
        swapped = 0;
        for (i = 1; i < n; i++) {
            if (a[i] < a[i - 1]) {
                t = a[i];
                a[i] = a[i - 1];
                a[i - 1] = t;
                swapped = 1;
            }
        }
    }
}
