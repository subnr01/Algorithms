#include <stdint.h>
#include <simics.h>
int main(){
    lprintf("fault incoming !");
    MAGIC_BREAK;
    int x = *((uintptr_t*)0xd0000000);
    lprintf("%x", x);
    x += 1;
    MAGIC_BREAK;
    return 0;
}
