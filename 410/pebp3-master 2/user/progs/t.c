#include <assert.h>
#include <stdio.h>
#include <stddef.h>
#include <syscall.h>
#include <simics.h>
#include "rand.h"

#include "thread.h"
#include "cond.h"
#include <sem.h>
#include "mutex.h"
#include "thrgrp.h"

int shared;

void *child(void *param);

#define STACK_SIZE 3072

#define NTHREADS 32
#define SOMETIMES 4


int main()
{
    shared = 0;

  thr_init(STACK_SIZE);
  sem_t sem;
  sem_init(&sem, 2);

  int t;
  for (t = 0; t < NTHREADS; ++t) {
    thr_create(child, (void *) &sem);
  }
  lprintf("main thread ends!");
  while(1);
  return 0;
}

/** @brief Declare that we have run, then twiddle thumbs. */
void *
child(void *param)
{
    sem_t *sem = (sem_t *) param;

    sem_wait(sem);
    shared++;
    lprintf("shared: %d", shared);
    sem_signal(sem);
    return NULL;
}
