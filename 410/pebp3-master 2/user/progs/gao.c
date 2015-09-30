#include <stdio.h>
#include <simics.h>
#include <syscall.h>

const char *hi="hi2";
int a=1;
int b[1<<12];

int main(int argc, char** argv)
{
    int i;
    for(i = 0; i < argc; i ++)
    {
        lprintf("argv %d: %s", i, argv[i]);
    }

    lprintf("%s from gao", hi);
    return 0;
}
