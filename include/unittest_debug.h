/*!
  @file unittest_debug.h
  @brief This is the interface for a C unit testing framework. It includes macros for controlling debug
  output and logging messages to the output stream. The provided macros allow you to activate the mute mode
  and redirect the output to /dev/null, as well as log new information to the output stream. This interface is
  designed to assist in debugging and logging during unit testing.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_DEBUG_INCLUDED
#define UNITTEST_DEBUG_INCLUDED

#include <stdio.h>
#include <stdbool.h>

#include "unittest_def.h"

typedef struct {
	const char *file, *unitcase;
	char msg[ERROR_INFO_MSG_SIZE];
	int   line;
} UnitTestCaseErrorInfo;

/* MUTE_ACTIVE: To mute the output of the test cases. */
#define MUTE_ACTIVE(BOOL) unittest_mute_active(BOOL)

/* LOG: Prints information through the actual debug file descriptor.  */
#define LOG(M, ...) dprintf(unittest_debug_fd_stdout, M __VA_OPT__(, ) __VA_ARGS__)

/* ERROR: Prints information through the error file descriptor.  */
#define ERROR(M, ...) dprintf(UNITTEST_STD_ERR, M __VA_OPT__(, ) __VA_ARGS__)

/* The file descriptor to know where to send the information. */
extern int unittest_debug_fd_stdout;

extern UnitTestCaseErrorInfo  *unittest_info_crashed_testcases[MAX_AMOUNT_OF_TESTCASES];

/* unittest_signal_error_str: Get the corresponding singal error msg, if testcase crashed. */
extern const char *unittest_signal_error_str(int signum);

/* unittest_mute_active: To mute or unmute the printed information. */
extern void unittest_mute_active(bool state);

/* unittest_print_crashed_testcase: To print the corresponding information from a crashed testcase  */
extern  void unittest_print_crashed_testcase(UnitTestCaseErrorInfo *info);

/* unittest_memory_cmp: Compares two blocks of memory and returns the index where they differ.
   If the function returns 'n', it means that the first 'n' bytes are equal. */
extern size_t unittest_memory_cmp(const char *var1, const char *var2, size_t n);

/* capture_n_hexvals: Captures the first n  hexadecimal values input hex_string. */
extern void capture_n_hexvals(const char *memory, size_t size, char *hex_string, size_t bsize);

#endif
