/** @file swexn.c
 *  @brief contains all relevent functions for installing, lauching, and
 *  interacting with the swexn system call.
 *
 *  To avoid large functions bits of code have been divided up into helper
 *  functions. We have ones for registering and deregistering the handler,
 *  sanity checking the registers, sanity checking esp0 and eip.
 *
 *  One nice thing to note is that we don't need a locking mechanism for
 *  registering and deregistering handlers, each thread has its own handler.
 *
 *  One function which is used by nearly every exception handler for which
 *  we support swexn, is the user_launch_handler function, which takes care
 *  of transfering control to the user handler.
 *
 *  An important design guideline behind the swexn implementation is safety
 *  checking just enough to ensure the kernel is not 
 *
 *  NOTE: we need to make sure calls to new and remove pages 
 *  do not remove our arguments before we are done, currently this is done
 *  through a page locking mechanism.
 *
 *  @author Alan Keith (arkeith)
 *  @author Hongchao Deng (hongchad)
 *
 *  @bugs No known bugs at this time 
 */
#include <stdint.h>
#include <ureg.h>
#include <stdint.h>
#include <tcb.h>
#include <cr.h>
#include <syscall_int.h>
#include <gateinst.h>
#include <cr.h>
#include <kernstk.h>
#include <tcb.h>
#include <swexn.h>
#include <common_macro.h>
#include <usermode.h>
#include <string.h>
#include <simics.h>
#include <seg.h>
#include <vmm.h>
#include <eflags.h>
#include <common_kern.h>
#include <pcb.h>
#define KERNLOG_L1_ON
#include <kernlog.h>


/** @brief mask to obtain only the bit values which we need to protect
 * Heres a reasoning behind the various eflags values
 * carry flag, not kernel's problem
 * resv1, reserved must be 1
 * parity flag, not kernel's problem
 * resv2, reserved, must be 0
 * af, not kernel's problem
 * resv3, reserved, must be 0
 * zf, not kernel's problem
 * sf, not kernel's problm 
 * tf, have kernel protect
 * if, interrupt flag, kernel protect
 * df, should kernel protect
 * of, not kernel's problem
 * iopl, kernel preserve
 * nt, nested task kernel preserve
 * resv4, must maintain 0 
 * rf, not kernel's problem
 * vm, kernel protect
 * ac, not kernel's problem
 * vif, kernel protect
 * vip, read only by system, can't be written, not our problem
 * id, kernel protect
 */
static unsigned int eflag_mustmatch = (EFL_RESV1 | EFL_RESV2 | EFL_RESV3 |
    EFL_TF | EFL_IF | EFL_DF | EFL_IOPL_RING3 | EFL_NT | EFL_RESV4 | EFL_VM | 
    EFL_VIF| EFL_ID | 0xFFC00000);//used to zero out bits which don't matter

/** @brief deregisters swexn handler for the active thread
 *
 *  we simply have to get the tcb data structure and 0 out swexn_esp3,
 *  user_handler, and args.
 */
void
deregister_swexn(){
    uintptr_t esp0;
    tcb_t *tcb;

    esp0 = get_esp0();
    tcb = (tcb_t *) esp0_to_tcb(esp0);
    tcb->swexn_esp3 = 0;
    tcb->user_handler = 0;
    tcb->args = 0;
}

/** @brief register a new swexn handler for the active thread
 *  
 *  we simply haveto initialize the appropriate fields in the 
 *  tcb data structure
 *
 *  @param esp3 the stack to run the user handler on
 *  @param handler the user exception handler
 *  @param arg an argument to pass to the handler when its invoked
 */ 
void
register_swexn(uintptr_t esp3, swexn_handler_t handler, void *arg){

    uintptr_t esp0;
    tcb_t *tcb;
    esp0 = get_esp0();
    tcb = (tcb_t *) esp0_to_tcb(esp0);
    tcb->swexn_esp3 = esp3;
    tcb->user_handler = handler;
    tcb->args = arg;
}

/** @brief sanity check esp3 and eip
 *  
 *  We want to make a few checks to ensure that these values won't crash
 *  the kernel when we invoke the exception handler
 *
 *  If esp3 is specified we need to make sure it won't mess with anything we
 *  have hidden above the user stack, we also need to make sure it wont mess
 *  with anything in the kernel.
 *
 *  For eip we need to do the exact same check.
 *
 *  Note that for eip we just make sure that USER_MEM_START < eip < MAX_VM_ADDR
 *  because the first user page is used for storing read only code. For esp we
 *  check that USER_MEM_START < esp3 < MAX_VM_ADDR + PAGE_SIZE. Although this 
 *  will generally avoid messing with this read only code, by ensuring we
 *  have atleast a PAGE_SIZE for pushing values onto the stack we ensure we
 *  don't overwrite kernel space.
 *
 *  Note that we can mess with things in user land, provided that it doesn't
 *  crash the kernel or mess with kernel data structures. We can limit damage
 *  caused by bad paramaters to the affect threads process in this case.
 * 
 *  @param esp3 potential stack location for handler
 *  @param eip first instruction of the user handler
 *  @return 0 if the parameters are unsafe, else retuns 1
 *
 */
int 
verify(uintptr_t esp3, uintptr_t eip){
    if (esp3){
        if ((esp3 < MAX_VM_ADDR) && (esp3 > USER_MEM_START + PAGE_SIZE)){
            vmm_flag_t flags = vmm_getflags(esp3);

            //is this location mapped in page table?
            if (!(flags & VMM_FLAG_PRESENT(VMM_FLAG_USER(0)))){
                return 0; //unsafe
            }
        }
        else{
            return 0;
        }
    }
    if (eip){
        if ((eip < MAX_VM_ADDR) && (eip > USER_MEM_START)){
            vmm_flag_t flags = vmm_getflags(eip);
            
            //is this location mapped in page table?
            if (!(flags & VMM_FLAG_PRESENT(VMM_FLAG_USER(0)))){
                return 0; //unsafe
            }
        }
        else{
            return 0;
        }
    }
    return 1;
}

/** @brief sanitize the passed register state
 *  
 *  A swexn handler can be given a null value for a register pointer, but
 *  when this value is not null we have a lot of safety checks to make.
 *  
 *  First it makes sense to check that accessing this pointer is not going to
 *  cause a page fault. We evaluate the passed registers and if non-zero make 
 *  sure they are reasonable values which won't cause problems for the kernel.
 *
 *  NOTE that by enforcing user level segmentation registers, even if
 *  the eip tries to execute into kernel land a protection fault will be 
 *  raised killing the thread. Note this is the user thread's handler
 *  dying, not the kernel dying.
 *
 *  NOTE we store our own copy on the kernel stack of the registers
 *  for safety reasons
 *
 * @param *passreg the passed register state
 * @param *newureg a location on the kernel stack to store our own copy
 * @param eflags an example eflags register (we assume correct)
 *
 * NOTE we normally take eflags from the ureg_t field pushed onto the
 * swexn handler stack, if we assume that this pushed value was correct
 *
 * NOTE we expect that other user threads will be unable to modify the memory
 * we are checking during this function (aka we expect we have page_lock)
 *
 * we can use it to compare.
 * @return 1 if safe, 0 if unsafe
 */
int 
check_newureg(ureg_t *passreg, ureg_t *newureg, unsigned int eflags){
    if (passreg){
        vmm_flag_t flags = vmm_getflags(passreg);
        if (flags & VMM_FLAG_PRESENT(0)){
            memcpy(newureg, passreg, sizeof(ureg_t));

            //check segment registers aren't trying to switch to kernel mode
            if (newureg->ds == SEGSEL_USER_DS
            && newureg->es == SEGSEL_USER_DS
            && newureg->fs == SEGSEL_USER_DS
            && newureg->gs == SEGSEL_USER_DS
            && newureg->ss == SEGSEL_USER_DS
            && newureg->cs == SEGSEL_USER_CS
            && (newureg->eflags & eflag_mustmatch) 
            == (eflags & eflag_mustmatch)) { //no changing eflag permission
                return 1; //safe
            }
        }
        return 0;
    }
    return 1;
}

/** @brief core of handling a swexn syscall 
 *
 * If esp3 and/or eip are zero deregister exception handler
 * else if both are non-zero attempt to register the handler
 *
 * if newureg is non-zero we adopt specified register values before
 * the system call returns to user space
 *
 * both requests must be carried out or neither will be
 * 
 *
 * We sanitize args (which is actually just ESI) and ensure we can actually
 * obtain the arguments we need, eflags is just the data which the trap
 * gate infrastruture psuhes onto the kernel stack,we know our own kernel
 * stack is safe.
 *
 * NOTE: We set a page lock because we don't new or remove pages causing 
 * problems, if we are switching register sets, we copy over the the reg
 * struct from user space ot kernel space such that when this lock is 
 * released we don't have to worry about race conditions with the register
 * area being freed by remove_pages.
 *
 * @param args this is the value of esi
 * @param eflags, this is the data pushed onto the kernel stack by syscall
 */
int 
swexn_handler(uintptr_t args, iret_t eflags){
    kernlog(5, "swexn handler being installed");
    uintptr_t esp3; //user handler stack
    swexn_handler_t eip; //user handler first instruction
    void *pass_arg;  //argument to pass to handler when invoked
    ureg_t *passreg;   //new register context to take on
    page_lock(); //no memory changing syscalls for now
    
    //sanitize args 
    vmm_flag_t flags = vmm_getflags(args);
    if (!(flags & VMM_FLAG_PRESENT(0))){ //ERROR, cannot read
        page_unlock();
        return -1; //bad args
    }
    flags = vmm_getflags(args+3*ADDR_BYTE);
    if (!(flags & VMM_FLAG_PRESENT(0))){ //ERROR, cannot read
        page_unlock();
        return -1; //bad args
    }
    //extract real parameters now
    esp3 = (uintptr_t) GET_ADDR_BYTE(args);
    args += ADDR_BYTE;
    eip = (swexn_handler_t) GET_FOUR_BYTE(args);
    args += ADDR_BYTE;
    pass_arg = (void*) GET_FOUR_BYTE(args);
    args += ADDR_BYTE;
    passreg = (ureg_t *) GET_FOUR_BYTE(args);

    ureg_t newureg;
    //to avoid a case where a user thread changes the registers after we've 
    //sanity checked them, we make an internal copy of the registers
    
    if (!check_newureg(passreg, &newureg, eflags.eflags)){ //validate safety of reg
        lprintf("%p passreg", passreg);
        page_unlock();
        return -1;
    }

    if (esp3 == 0 || eip == 0){
        deregister_swexn();
    }
    else{
        if (!verify(esp3, (uintptr_t) eip)){
            page_unlock();
            return -1;
        }
        register_swexn(esp3, eip, pass_arg);
    }
    if (passreg){ //use our copy of the registers
        page_unlock(); //if user dies from bad registers, its a user crash
        swexn_restore_reg(newureg);
        return -1;
    }
    else{
        page_unlock();
        return 0;
    }
}

/** @brief simple function for installing swexn syscall handler in idt
 */
void
swexn_install()
{
    uintptr_t funcaddr;
    uintptr_t gateaddr;

    gateaddr = get_gateaddr(SWEXN_INT);

    funcaddr = (uintptr_t) ( &swexn_wrapper);

    trap_gateinst(gateaddr, funcaddr, DPL_USER);
}


/** @brief invokes the installed user exception handler
 *
 * We want to get enough state pushed to the user stack
 * such that everything can just execute in user mode, isolating
 * us from user handler problems.
 *
 * NOTE: stack is one word higher than the first address which we 
 * can push values onto the stack
 *
 * we double check esp, but if the eip is no longer valid its not our 
 * fault, if we jump there we will be in user mode, its will be a
 * user fault, not a kernel fault
 *
 * Note that because this function is only called by exception handlers,
 * we don't need to perform any additional sanitization of arguments
 *
 * @param *arg the argument to pass to handler
 * @param *state ureg_t at the time of exception
 * @param esp the stack to use for the handler
 * @param handler, the stored eip to use when handler is invoked
 */
void user_handler_launcher(void *arg, ureg_t *state, uintptr_t esp, 
    swexn_handler_t handler){
    
    page_lock();//check stack

    vmm_flag_t flags = vmm_getflags(esp);
    if (!( (flags & VMM_FLAG_PRESENT(0)) && 
        (flags & VMM_FLAG_USER(0)) && 
        (flags & VMM_FLAG_READWRITE(0)))){ //ERROR, cannot use stack
        page_unlock();
        return; //esp stack top no longer valid
    }
    flags = vmm_getflags(esp -
        sizeof(uintptr_t)-
            sizeof(ureg_t)-
            sizeof(uintptr_t)-
            sizeof(void*)-
            sizeof(uintptr_t)); //check last place where we will push
    
    flags = vmm_getflags(esp);
    if (!( (flags & VMM_FLAG_PRESENT(0)) && 
        (flags & VMM_FLAG_USER(0)) && 
        (flags & VMM_FLAG_READWRITE(0)))){ //ERROR, cannot use stack
        page_unlock();
        return; //esp stack bottom no longer valid
    }
    
    uintptr_t stack = esp - sizeof(uintptr_t);
    
    kernlog(5, "stack %x", stack);
    stack -= sizeof(ureg_t);
    memcpy((void*)stack, state, sizeof(ureg_t));

    kernlog(5, "saved registers %x", stack);
    stack -= sizeof(uintptr_t);
    (*((uintptr_t*)stack)) = (stack +sizeof(uintptr_t));
    
    kernlog(5,"saved register pointer addr %x points to %x ", 
        stack, stack+sizeof(uintptr_t));

    stack -= sizeof(void*);
    (*((uintptr_t*)stack)) = (uintptr_t) arg;
    
    kernlog(5, "saved arged %x", stack);
    page_unlock();
    //stack prepared, nothing else will be pushed onto the stack from kernel
    //from here on out problems will be cause by user
    run_user((int)handler, stack-sizeof(uintptr_t));
}
