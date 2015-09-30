/** @file idt_inst.h
 *  @brief syscall install function declaration file
 */
#ifndef _IDT_INST_H
#define _IDT_INST_H

void timer_install();
void gettid_install();
void fork_install();
void thread_fork_install();
void exec_install();
void keyboard_install();
void wait_install();
void vanish_install();
void set_status_install();
void sleep_install();
void readline_install();
void yield_install();
void make_runnable_install();
void deschedule_install();
void new_pages_install();
void remove_pages_install();
void print_install();
void readfile_install();
void halt_install();
void set_term_color_install();
void get_ticks_install();
void set_cursor_pos_install();
void get_cursor_pos_install();


void pagefault_install();
void swexn_install();
void has_ecode_install();
void no_ecode_install();


#endif // for #ifndef _IDT_INST_H
