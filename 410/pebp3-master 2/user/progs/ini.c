/** @file 410user/progs/init.c
 *  @author ?
 *  @brief Initial program.
 *  @public yes
 *  @for p2 p3
 *  @covers fork exec wait print
 *  @status done
 */

#include <syscall.h>
#include <stdio.h>
#include <simics.h>

int main()
{
  int pid, exitstatus;
  char shell[] = "sh";
  char * args[] = {shell, 0};

  int counter = 0;
  while(1) {
    pid = fork();
    if (!pid)
      exec(shell, args);
    
    while ( ( pid = wait(&exitstatus) )){
        lprintf("init reap an item, counter: %d, pid: %d", counter, pid);
        counter++;
    }
  
    printf("Shell exited with status %d; starting it back up...", exitstatus);
  }
}
