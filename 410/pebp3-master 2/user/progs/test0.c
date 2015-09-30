#include <syscall.h>
#include <stdlib.h>
#include <simics.h>
#include <stdio.h>

void abc(int a)
{
    int *b;
    while(1){
MAGIC_BREAK;
        b = malloc(sizeof(int));
        /*lprintf("address: 0x%.8x", (unsigned) (b));*/

    }
}

int main(int argc, char **argv)
{
    lprintf("hello,world");
    abc(1);
    exit(0);
}
