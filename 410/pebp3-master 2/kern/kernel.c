/** @file kernel.c
 *  @brief An initial kernel.c
 *
 *  This is the entry file for P3 kernel. We're setting up IDT entries,
 *  activating memory, doing a whole bunch of initialization for all
 *  modules, and create and load the first process (normally 'init') in
 *  this file within kernel_main() function.
 *
 *  @author Hongchao Deng (hongchad)
 *
 *  @bug No known bugs.
 */

#include <common_kern.h>

/* libc includes. */
#include <stdio.h>

/* multiboot header file */
#include <multiboot.h>              /* boot_info */

/* x86 specific includes */
#include <x86/asm.h>                /* enable_interrupts() */

#include <_malloc.h>
#include <loader.h>
#include <vmm.h>
#include <pmm.h>
#include <idt.h>
#include <pcb.h>
#include <kernstk.h>
#include <cr.h>
#include <scheduler.h>
#include <cpu.h>
#include <assert.h>
#include <idle.h>
#include <console.h>
#include <tid_table.h>
#include <sleep_lib.h>
#include <console_io.h>
#include <_wait.h>
#include <malloc.h>
#include <res_manage.h>

#define KERNLOG_L1_ON
#include <kernlog.h>

/** @brief Kernel entrypoint.
 *
 *  This is the entrypoint for the kernel.
 *
 *  @return Does not return
 */
int kernel_main(mbinfo_t *mbinfo, int argc, char **argv, char **envp)
{
    /*
     * When kernel_main() begins, interrupts are DISABLED.
     * You should delete this comment, and enable them --
     * when you are ready.
     */
    uintptr_t esp0;
    pcb_t *pcb;
    tcb_t *tcb;
    int cr3;

    /* idt table set up */{
        idt_setup();
        intr_ok = 0; // for IRQ 7
        enable_interrupts();
    }

    /* init functions */ {
        malloc_init();

        // memory
        pmm_init();
        activate_vm();

        // scheduling, tid table, syscall, console
        scher_init();
        tidtable_init();
        sleep_init();
        console_io_init();
        init_console();
    }

    /* set up the first process */{
        cr3 = get_cr3();
        assert( (pcb = create_process(NULL, cr3)) != NULL );

        set_init_pcb(pcb); // set it as process 'init'

        tcb = get_only_thread(pcb);
        esp0 = tcb_to_esp0( (uintptr_t) tcb );

        // added to run queue
        scher_add_newlycreated(tcb);

        set_esp0(esp0);
    }

    //MAGIC_BREAK;
    // create idle process (after set_esp0 for first one)
    idle_init();

    // put the first thread in cpu
    cpu_init();

    intr_ok = 1; // for IRQ 7

    process_num = 0; // for resource manager

    //char* elf_argv[] = {"test", "arg1", "arg2", NULL};
    //char* elf_argv[] = {"gao", "arg1", "arg2", NULL};
    //char* elf_argv[] = {"slaughter", "fork_wait_bomb", "3","3","0", NULL};
    //char* elf_argv[] = {"slaughter", "fork_exit_bomb", "3","3","0", NULL};
    //char* elf_argv[] = {"slaughter", "make_crash", "3","3","0", NULL};
    //char* elf_argv[] = {"ini", NULL};
    char* elf_argv[] = {"init", NULL};
    load_elf(elf_argv[0], elf_argv);

    kernlog(1, "hehehe...");
    while(1){
        continue;
    }

    return 0;
}
