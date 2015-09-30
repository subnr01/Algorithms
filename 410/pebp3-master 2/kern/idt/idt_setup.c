/** @file idt_setup.c
 *  @brief install all syscalls.
 */
#include <idt_inst.h>

void
idt_setup()
{
    timer_install();
    keyboard_install();

    /********** SYSCALL ***************/
    gettid_install();
    fork_install();
    thread_fork_install();
    exec_install();
    wait_install();
    vanish_install();
    set_status_install();
    sleep_install();
    yield_install();
    make_runnable_install();
    readline_install();
    deschedule_install();
    new_pages_install();
    remove_pages_install();
    print_install();
    readfile_install();
    halt_install();
    get_ticks_install();
    set_term_color_install();
    set_cursor_pos_install();
    get_cursor_pos_install();

    /********** EXCEPTION ***********/
    pagefault_install();
    swexn_install();
    has_ecode_install();
    no_ecode_install();
}
