/** @file invl_tlb.h
 *  @brief invalidate tlb entry module header file
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 */
#ifndef _INVL_TLB_H
#define _INVL_TLB_H

/** @brief flush TLB entry for given logical address
 */
void invl_tlb(uintptr_t addr);

#endif // for #ifndef _INVL_TLB_H
