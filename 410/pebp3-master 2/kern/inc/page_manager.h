/** @file page_manager.h
 *  @brief This module is used for new_pages and remove_pages syscall
 *  relevant things.
 *
 *  For those two syscalls, we're using the 11th bit (reserved) of page
 *  permission to mark the start, and 10th bit to mark the end of a
 *  allocated region by new_pages syscalls. We need to use this because
 *  the remove_pages only gives the starting address and we also need to
 *  check the validity of starting address too.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 */
#ifndef _PAGE_MANAGER_H
#define _PAGE_MANAGER_H

#define PAGE_MARK_START(flag) ( (flag) | 0x800)
#define PAGE_MARK_END(flag) ( (flag) | 0x400)

#define TEST_PAGE_START(flag) (( (flag) & PAGE_MARK_START(0)))
#define TEST_PAGE_END(flag) (( (flag) & PAGE_MARK_END(0)))

#endif // for #ifndef _PAGE_MANAGER_H
