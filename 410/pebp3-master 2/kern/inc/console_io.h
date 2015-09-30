/** @file console_io.h
 *  @brief console io module header file
 *
 *  @author Hongchao Deng (hongchad)
 */
#ifndef _CONSOLE_IO_H
#define _CONSOLE_IO_H

#include <tcb.h>

#define KEYBUF_SIZE 1024

int readchar();

void console_io_init();
void console_io_wait(tcb_t *tcb);
int console_io_has_waiting();
void console_io_wakeup_next();

#endif // for #ifndef _CONSOLE_IO_H
