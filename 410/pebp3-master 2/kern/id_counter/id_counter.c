/** @file id_counter.c
 *  @brief Provides id counter for thread id
 *
 *  @author Hongchao Deng (hongchad)
 *  @author Alan Keith (arkeith(
 *  @bugs no known bugs
 *
 */
#include <id_counter.h>

#define IDCOUNTER_START (0)

/** @brief get a new thread id
 * @return a new id
 */
int
get_tid_counter()
{
    static int tid_counter = IDCOUNTER_START;
    int res;

    res = __sync_fetch_and_add( & tid_counter,1);
    // we don't want negative id
    return (res & ~0x80000000);
}

