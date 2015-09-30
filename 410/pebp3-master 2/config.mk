###########################################################################
#
#    #####          #######         #######         ######            ###
#   #     #            #            #     #         #     #           ###
#   #                  #            #     #         #     #           ###
#    #####             #            #     #         ######             #
#         #            #            #     #         #
#   #     #            #            #     #         #                 ###
#    #####             #            #######         #                 ###
#
#
# Please read the directions in README and in this config.mk carefully.
# Do -N-O-T- just dump things randomly in here until your kernel builds.
# If you do that, you run an excellent chance of turning in something
# which can't be graded.  If you think the build infrastructure is
# somehow restricting you from doing something you need to do, contact
# the course staff--don't just hit it with a hammer and move on.
#
# [Once you've read this message, please edit it out of your config.mk]
# [Once you've read this message, please edit it out of your config.mk]
# [Once you've read this message, please edit it out of your config.mk]
###########################################################################

###########################################################################
# This is the include file for the make file.
# You should have to edit only this file to get things to build.
###########################################################################

###########################################################################
# Tab stops
###########################################################################
# If you use tabstops set to something other than the international
# standard of eight characters, this is your opportunity to inform
# our print scripts.
TABSTOP = 4

###########################################################################
# The method for acquiring project updates.
###########################################################################
# This should be "afs" for any Andrew machine, "web" for non-andrew machines
# and "offline" for machines with no network access.
#
# "offline" is strongly not recommended as you may miss important project
# updates.
#
UPDATE_METHOD = afs

###########################################################################
# WARNING: When we test your code, the two TESTS variables below will be
# blanked.  Your kernel MUST BOOT AND RUN if 410TESTS and STUDENTTESTS
# are blank.  It would be wise for you to test that this works.
###########################################################################

###########################################################################
# Test programs provided by course staff you wish to run
###########################################################################
# A list of the test programs you want compiled in from the 410user/progs
# directory.
#
410TESTS = actual_wait cat cho2 cho cho_variant chow ck1 coolness\
	    minclone_mem readline_basic fork_bomb fork_exit_bomb fork_wait\
	    exec_basic exec_nonexist sleep_test1 fork_wait_bomb\
	    exec_basic_helper wait_getpid wild_test1 print_basic slaughter\
	    deschedule_hang loader_test1 loader_test2 knife peon merchant work\
	    yield_desc_mkrun make_crash make_crash_helper new_pages\
	    remove_pages_test1 remove_pages_test2 mem_permissions register_test\
		swexn_basic_test swexn_cookie_monster swexn_dispatch swexn_regs \
		swexn_stands_for_swextensible swexn_uninstall_test stack_test1

###########################################################################
# Test programs you have written which you wish to run
###########################################################################
# A list of the test programs you want compiled in from the user/progs
# directory.
#
STUDENTTESTS = ini sh test feb gao sl rpt cv

###########################################################################
# Data files provided by course staff to build into the RAM disk
###########################################################################
# A list of the data files you want built in from the 410user/files
# directory.
#
410FILES =

###########################################################################
# Data files you have created which you wish to build into the RAM disk
###########################################################################
# A list of the data files you want built in from the user/files
# directory.
#
STUDENTFILES =

###########################################################################
# Object files for your thread library
###########################################################################
THREAD_OBJS = malloc.o panic.o \
	mutex.o thread_queue.o atomic_swap.o cond.o sem.o rwlock.o\
	thread_fork.o thread.o thr_init.o thr_exit_join.o thread_create.o \
	autostack_wrapper.o
#THREAD_OBJS = malloc.o panic.o

# Thread Group Library Support.
#
# Since libthrgrp.a depends on your thread library, the "buildable blank
# P3" we give you can't build libthrgrp.a.  Once you install your thread
# library and fix THREAD_OBJS above, uncomment this line to enable building
# libthrgrp.a:
410USER_LIBS_EARLY += libthrgrp.a

###########################################################################
# Object files for your syscall wrappers
###########################################################################
SYSCALL_OBJS = print.o vanish.o fork.o set_status.o\
	       yield.o deschedule.o make_runnable.o sleep.o task_vanish.o\
	       remove_pages.o misbehave.o getchar.o halt.o\
	       get_cursor_pos.o gettid.o new_pages.o readfile.o readline.o\
	       set_cursor_pos.o swexn.o wait.o exec.o set_term_color.o \
		   get_ticks.o
#SYSCALL_OBJS = syscall.o\
	       gettid.o exec.o sleep.o readline.o fork.o set_status.o vanish.o\
	       deschedule.o yield.o make_runnable.o wait.o print.o readfile.o\

###########################################################################
# Parts of your kernel
###########################################################################
#
# Kernel object files you want included from 410kern/
#
410KERNEL_OBJS = load_helper.o
#
# Kernel object files you provide in from kern/
#
KERNEL_OBJS = console.o kernel.o  malloc_wrappers.o \
	vm_manager/vm_installer.o vm_manager/page_allocator.o vm_manager/mapper.o\
	vm_manager/switch_vmm.o\
	vm_manager/frame_allocator.o vm_manager/frame_alloc.o\
	vm_manager/invl_tlb.o\
	vm_manager/vmm_getflags.o vm_manager/vmm_loader.o\
	vm_manager/vmm_check.o\
	vm_manager/page_cloner.o vm_manager/vm_release.o\
	loader/loader.o loader/loader_vmm.o loader/loader_stkprep.o\
	idle/idle.o\
	mode_switch/run_user.o\
	idt/idt_setup.o idt/gateinst.o\
	interrupt/timer/timer.o interrupt/timer/timer_wrapper.o\
	interrupt/keyboard/keyboard.o interrupt/keyboard/keyboard_wrapper.o\
	queue/queue.o\
	sched/scheduler.o sched/yield_to.o sched/desche.o\
	cpu/cpu.o\
	pcb/pcb.o\
	tcb/tcb.o\
	idle/idle.o\
	id_counter/id_counter.o\
	klock/spinlock.o klock/mutex.o\
	conswi/switch_cpustate.o\
	skiplist/skiplist.o tcb/tid_table.o\
	binheap/binheap.o\
	sleep/sleep.o\
	console/console_io.o\
	wait/wait.o\
	syscall/gettid/gettid.o syscall/gettid/gettid_wrapper.o\
	syscall/fork/fork.o syscall/fork/fork_wrapper.o syscall/fork/prep_childstk.o syscall/fork/push_all_general_regs.o\
	syscall/fork/thread_fork.o\
	syscall/wait/wait.o syscall/wait/wait_wrapper.o\
	syscall/sleep/sleep.o syscall/sleep/sleep_wrapper.o\
	syscall/readline/readline.o syscall/readline/readline_wrapper.o\
	syscall/readfile/readfile.o syscall/readfile/readfile_wrapper.o\
	syscall/vanish/vanish.o syscall/vanish/vanish_wrapper.o\
	syscall/set_status/set_status.o syscall/set_status/set_status_wrapper.o\
	syscall/exec/exec.o syscall/exec/exec_wrapper.o\
	syscall/yield/yield.o syscall/yield/yield_wrapper.o\
	syscall/halt/halt.o syscall/halt/halt_wrapper.o\
	syscall/print/print.o syscall/print/print_wrapper.o\
	syscall/set_cursor_pos/set_cursor_pos.o syscall/set_cursor_pos/set_cursor_pos_wrapper.o\
	syscall/get_cursor_pos/get_cursor_pos.o syscall/get_cursor_pos/get_cursor_pos_wrapper.o\
	syscall/set_term_color/set_term_color.o syscall/set_term_color/set_term_color_wrapper.o\
	syscall/get_ticks/get_ticks.o syscall/get_ticks/get_ticks_wrapper.o\
	syscall/make_runnable/make_runnable.o syscall/make_runnable/make_runnable_wrapper.o\
	syscall/deschedule/deschedule.o syscall/deschedule/deschedule_wrapper.o\
	syscall/new_pages/new_pages.o syscall/new_pages/new_pages_wrapper.o\
	syscall/remove_pages/remove_pages.o syscall/remove_pages/remove_pages_wrapper.o\
	syscall/swexn/swexn.o syscall/swexn/swexn_wrapper.o\
	exception/pagefault/zfod.o exception/pagefault/pagefault.o exception/pagefault/pagefault_wrapper.o\
	exception/has_ecode/has_ecode.o exception/has_ecode/has_ecode_wrapper.o\
	exception/no_ecode/no_ecode.o exception/no_ecode/no_ecode_wrapper.o\
	exception/exception.o

###########################################################################
# WARNING: Do not put **test** programs into the REQPROGS variables.  Your
#          kernel will probably not build in the test harness and you will
#          lose points.
###########################################################################

###########################################################################
# Mandatory programs whose source is provided by course staff
###########################################################################
# A list of the programs in 410user/progs which are provided in source
# form and NECESSARY FOR THE KERNEL TO RUN.
#
# The shell is a really good thing to keep here.  Don't delete idle
# or init unless you are writing your own, and don't do that unless
# you have a really good reason to do so.
#
410REQPROGS = idle init shell

###########################################################################
# Mandatory programs whose source is provided by you
###########################################################################
# A list of the programs in user/progs which are provided in source
# form and NECESSARY FOR THE KERNEL TO RUN.
#
# Leave this blank unless you are writing custom init/idle/shell programs
# (not generally recommended).  If you use STUDENTREQPROGS so you can
# temporarily run a special debugging version of init/idle/shell, you
# need to be very sure you blank STUDENTREQPROGS before turning your
# kernel in, or else your tweaked version will run and the test harness
# won't.
#
STUDENTREQPROGS =

