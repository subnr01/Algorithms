/** @file cpu.c
 *  @brief cpu module implementation file
 *
 *  This is cpu module. The cpu is managing operations that entering and
 *  exiting cpu (context switch). When doing this, because no one is
 *  inside the cpu running now, we're disabling interrupts because
 *  there's no need to service it. We also need to protect the run queue
 *
 *  Roughly this module handles
 *  peripheral operations for context switch. This happens when running
 *  thread is going to be switched out (yield, timer goes off, etc.). In
 *  this case the runnning thread will be pushed back to the FIFO
 *  scheduler run queue and get the first item out to run.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 *
 *  @bug No known bugs.
 */
#include <cpu.h>
#include <pcb.h>
#include <tcb.h>
#include <asm.h>
#include <stddef.h>
#include <scheduler.h>
#include <queue.h>
#include <kernstk.h>
#include <cr.h>
#include <idle.h>
#include <conswi.h>
#include <assert.h>
#include <malloc_internal.h>
#include <switch_vmm.h>
#include <res_manage.h>

#define KERNLOG_L1_ON
#include <kernlog.h>


// the only CPU. we might need to do more on this module for multi
// processor.
static cpu_t cpu;


/** @brief cpu initialization.
 *
 *  Technically it just gets the only thread in run queue.
 *
 *  @return Void.
 */
void
cpu_init()
{
    assert( (cpu.run_job = scher_pop_job() ) != NULL );
}


/*
 * These are allocated as global values so that it doesn't depend on
 * the kernel stack of each threads.
 */
static tcb_t *prev_tcb;
static tcb_t *next_tcb;
static uintptr_t _very_temp_esp;

/** @brief running thread relaxes control of cpu.
 *
 *  This is the actual context switch function. The running thread gives
 *  up the cpu and switch between different stats to the next thread in
 *  run queue.
 *
 *  There's always one thread running in CPU. If everyone's blocked,
 *  then the idle process is waken up and run in cpu.
 *
 *  @return Void.
 */
void cpu_relax()
{
    // switching between threads


    // protect run queue
    disable_interrupts(); {


        // no other runnable thread.
        //   1. if current one is running, doesn't need to switch
        //   2. otherwise (blocked), get idle to run
        if( scher_no_other_runthr() ){
            if( is_thr_active( cpu.run_job ) ){
                enable_interrupts();
                return;
            }
            else{
                kernlog(1, "get idle next, process_num: %d, freeframe: %d",
                  process_num, res_count_freeframe());
                get_idle_next();
            }
        }

        // get current running as previous
        assert( (prev_tcb = cpu.run_job) != NULL);{
            // we don't need to put blocked thread into runqueue
            // if the thread isn't active or it's idle and there's
            // runnable thread now.
            if(  is_thr_active(prev_tcb) && ! I_am_idle(prev_tcb) ){

                kernlog(5, "pushed back to run queue");
                // put it back to scheduler run queue
                scher_push_job(prev_tcb);
            }
        }

        // get next one in run queue. (always one next here)
        assert( (next_tcb= cpu.run_job= scher_pop_job()) != NULL );{

            kernlog(5, "switching  between: %d %d", prev_tcb->tid, next_tcb->tid);

            // context switch

            // memory switch{
                save_remap( & prev_tcb->remap);

                // switch page tables for different processes
                if(next_tcb->pcb != prev_tcb->pcb)
                    set_cr3(next_tcb->pcb->cr3);

                restore_remap( & next_tcb->remap);
            // }

            // set esp0 for next thread
            set_esp0( (uint32_t) tcb_to_esp0( (uintptr_t) next_tcb) );

            if( is_thr_dead(prev_tcb) ){
                // free resources (tcb) for the dead thread.
                _free(prev_tcb);
                switch_cpustate(& _very_temp_esp, next_tcb->save_esp);
            }
            else{
                // normal switching states.
                switch_cpustate(& prev_tcb->save_esp, next_tcb->save_esp);
            }

            if( is_thr_ioblocked(next_tcb) ){
                // do not enable the interrupts so that the readline
                // blocked one could continue to read until he finishes
                return;
            }

        }

    } enable_interrupts();
}



