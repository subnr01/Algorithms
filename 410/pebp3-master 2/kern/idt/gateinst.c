/** @file gateinst.c
 *  @brief helper function to encapsulate the details of installing trap
 *  or interrupt gate in IDT table.
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith)
 */
#include <seg.h>
#include <asm.h>
#include <stdint.h>

// This struct is used for accessing the two 32bytes gate entry.
typedef struct _idt_gate_t {
    uint32_t *data;
} idt_gate_t;

// size of each entry in idt is 8 bytes
#define IDT_ENTRYSIZE 8

uintptr_t
get_gateaddr(unsigned int entry_num)
{
    return (uintptr_t) idt_base() +
      (uintptr_t) (IDT_ENTRYSIZE * entry_num);
}

void
trap_gateinst(uintptr_t gate_addr, uintptr_t funcaddr, int dpl)
{
    idt_gate_t gate;
    gate.data = (uint32_t *) gate_addr;

    gate.data[0] = ( ( SEGSEL_KERNEL_CS << 16 ) // segment selector
                    | ( funcaddr & 0x0000FFFF ) // 15..0 bits of offset
                    );
    gate.data[1] = ( ( funcaddr & 0xFFFF0000 ) // 31..16 bits of offset
                    | (1 << 15 ) // present bit
                    | (dpl << 13) // descriptor privilege level
                    | (0xF << 8) // size of gate is 32 bits
                    );
}

void
interrupt_gateinst(uintptr_t gate_addr, uintptr_t funcaddr, int dpl)
{
    idt_gate_t gate;
    gate.data = (uint32_t *) gate_addr;

    gate.data[0] = ( ( SEGSEL_KERNEL_CS << 16 ) // segment selector
                    | ( funcaddr & 0x0000FFFF ) // 15..0 bits of offset
                    );
    gate.data[1] = ( ( funcaddr & 0xFFFF0000 ) // 31..16 bits of offset
                    | (1 << 15 ) // present bit
                    | (dpl << 13) // descriptor privilege level
                    | (0xE << 8) // size of gate is 32 bits
                    );
}
