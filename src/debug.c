/*!
  @file debug.c
  @brief The source code for unittest_debug.h, which contains the filedescriptor where to print the
  information.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_def.h"
#include "../include/unittest_debug.h"

#include <assert.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/signal.h>

_Static_assert(MAX_AMOUNT_OF_TESTCASES == 1024, "This should 1024 testscases");

UnitTestCaseErrorInfo  *unittest_info_crashed_testcases[MAX_AMOUNT_OF_TESTCASES];

_Static_assert(UNITTEST_STD_OUT == 1, "This initialy should be 1");

int unittest_debug_fd_stdout = UNITTEST_STD_OUT, unittest_mute_mode = 0;

/* unittest_mute_active: To mute or unmute the printed information. */
void unittest_mute_active(bool state)
{
	if (state) {
		unittest_mute_mode = 1;					\
		unittest_debug_fd_stdout = open("/dev/null", O_WRONLY);	\
	} else {
		if (unittest_debug_fd_stdout > 3)
			close(unittest_debug_fd_stdout);
		
		unittest_mute_mode = 0;				
		unittest_debug_fd_stdout = UNITTEST_STD_OUT;	
	}
}

/* unittest_signal_error_str: Get the corresponding singal error msg, if testcase crashed. */
const char *unittest_signal_error_str(int signum)
{
	switch (signum) {
	case SIGSEGV: return "Segmentation fault (SIGSEGV): Invalid memory access";
	case SIGABRT: return "Aborted (SIGABRT): Program has been explicitly aborted";
	case SIGILL: return "Illegal Instruction (SIGILL): Invalid machine instruction";
	case SIGFPE:
		return "Floating-Point Exception (SIGFPE): Illegal floating-point "
		       "operation";
	case SIGBUS: return "Bus Error (SIGBUS): Invalid memory access or misalignment";
	case SIGTRAP: return "Trace Trap (SIGTRAP): Debugging event";
	case SIGSYS: return "Bad System Call (SIGSYS): Invalid system call";
	case SIGPIPE: return "Broken Pipe (SIGPIPE): Write to a closed pipe/socket";
	case SIGXCPU:
		return "Cputime Limit Exceeded (SIGXCPU): Process exceeded CPU time "
		       "limit";
	case SIGXFSZ:
		return "File Size Limit Exceeded (SIGXFSZ): Process exceeded file size "
		       "limit";
	default: return "Unknown Signal";
	}
}

/* unittest_print_crashed_testcase: To print the corresponding information from a crashed testcase  */
void unittest_print_crashed_testcase(UnitTestCaseErrorInfo *info)
{
	LOG("==========================================================================="
	    "===========\n");

	LOG("ERROR:\t\t(%s)\n", info->unitcase);
	LOG("---------------------------------------------------------------------------"
	    "-----------\n");
	LOG("Traceback...\n");
	LOG("\tFile \"%s\", line %i, in %s\n", info->file, info->line, info->unitcase);
	LOG("ErrorDescription:\t \"%s\"\n\n", info->msg);
}

