#include <stdint.h>
#include <syscall_int.h>
#include <gateinst.h>
#include "yield.h"
#include <sched.h>

/** @brief yield handler
 *  @return 0 on success. negative number on failure.
 */
int
yield_handler(int tid)
{
    return yield_to(tid);
}

void
yield_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(YIELD_INT);

    funcaddr = (uintptr_t) ( &yield_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);

}
