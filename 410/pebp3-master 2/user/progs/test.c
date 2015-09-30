#ifndef _TEST_C
#define _TEST_C
#include <stdio.h>
#include <simics.h>
#include <syscall.h>

const char *hi="hi";
int a=1;
int b[1<<12];

void always_loop()
{
    while(1);
}

int main()
{
    lprintf("%s",hi);

    char *argv[] = {"abc", "arg1", "arg2", NULL};

    exec("gao", argv);
    lprintf("!!!horribly wrong!!!");

    //int pid;
    //if( ( pid = fork()) != 0){
        //lprintf("spawn: pid(%d)", pid);
        //while(make_runnable(pid) != 0) yield(pid);
        //lprintf("make run successfully");
    //}
    //int temp = 0;
    //deschedule(& temp);
    //lprintf("successfully woken up: pid(%d)", gettid());

    //int pid;
    //int status;
    //if( (pid = fork()) != 0)
    //{
        //wait(&status);
        //lprintf("exit status: %d", status);
    //}
    //else
        //return 15410;

    //int pid;
    //int status;
    //while(1 ){
        //pid = fork();
        //if( pid == -1){
            //lprintf("fork failed");
            //break;
        //}
        //if(gettid() == 0 || gettid() % 2 == 1)
            //wait(&status);
    //}

    //if(gettid() == 0)
        //while(1);

    return 0;
}
#endif // for #ifndef _TEST_C
