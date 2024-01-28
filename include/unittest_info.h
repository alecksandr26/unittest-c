/*!
  @file unittest_info.h
  @brief

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_INFOFAIL_INCLUDE
#define UNITTEST_INFOFAIL_INCLUDE

#include "unittest_assert.h"
#include "unittest_debug.h"
#include "unittest_def.h"
#include "unittest_expect.h"

#include <string.h>

#define _UNITTEST_UNKNOWN_DTYPE "unknown"

#define _UNITTEST_DTYPES_C_FORMAT(X)   \
	_Generic((X),                  \
		 int: "%i",				\
		 long: "%li",				\
		 short: "%hi",				\
		 unsigned: "%u",			\
		 unsigned long: "%lu",			\
		 unsigned short: "%hu",			\
		 double: "%lf",				\
		 float: "%f",				\
		 char: "%c",				\
		 char *: "%s",				\
		 void *: "%p",				\
		default: _UNITTEST_UNKNOWN_DTYPE)

#define _UNITTEST_FIRST(X, ...) X

#define _UNITTEST_CATCH_INFO(INFO, LINE, MSG, TEST) \
	do {                                        \
		(INFO)->line = LINE;                \
		(INFO)->msg  = MSG;                 \
		(INFO)->test = TEST;                \
	} while (0)

#define _UNITTEST_CATCH_COMPARISON_INFO(INFO, X, Y, VAR1, VAR2, COMP)                    \
	do {                                                                             \
		char	    output[INFO_MSG_SIZE];			\
		const char *format = _UNITTEST_DTYPES_C_FORMAT(X);	\
		if (strcmp(format, _UNITTEST_UNKNOWN_DTYPE) == 0) {	\
			size_t n =					\
				(sizeof(unittest_var1) < 5) ? sizeof(unittest_var1) : 5; \
			size_t nb = n * 2 + 1;                                           \
			char   hex_vals_var1[nb];                                        \
			char   hex_vals_var2[nb];                                        \
			capture_n_hexvals(((char *) &VAR1), n, hex_vals_var1, nb);       \
			capture_n_hexvals(((char *) &VAR2), n, hex_vals_var2, nb);       \
			sprintf(output,                                             \
				"%s %s %s, where %s = 0X%s... and %s = 0X%s... "         \
				"have unknown data types",                               \
				#X, COMP, #Y, #X, hex_vals_var1, #Y, hex_vals_var2);     \
			strcpy(INFO->expr, output);                                 \
		} else {                                                                 \
			sprintf(output, "%s %s %s, where %s = %s and %s = %s", #X,  \
				COMP, #Y, #X, format, #Y, format);                       \
			sprintf(INFO->expr, output, X, Y);                          \
		}                                                                        \
	} while (0)


#define INFO(M, ...)				\
	do {					\
		UnitTestInfo    *info = &unitcase->info;		\
		UnitTestInfoMsg *info_msg =				\
			&info->info_msgs[info->number_info_msgs++];	\
		info_msg->test = unitframe.current_test;			\
		info_msg->line = __LINE__;				\
		sprintf(info_msg->msg, M __VA_OPT__(,) __VA_ARGS__);	\
	} while (0)


#define INFO_VAR(VAR)				\
	do {								\
		UnitTestInfo    *info = &unitcase->info;		\
		UnitTestInfoMsg *info_msg =				\
			&info->info_msgs[info->number_info_msgs++];	\
		info_msg->test = unitframe.current_test;		\
		info_msg->line = __LINE__;				\
		const char *format = _UNITTEST_DTYPES_C_FORMAT(VAR);	\
		char	    output[INFO_MSG_SIZE];			\
		if (strcmp(format, _UNITTEST_UNKNOWN_DTYPE) == 0) {	\
			size_t n =					\
				(sizeof(VAR) < 5) ? sizeof(VAR) : 5;	\
			size_t nb = n * 2 + 1;				\
			char   hex_vals_var[nb];			\
			capture_n_hexvals(((char *) &VAR), n, hex_vals_var, nb); \
			sprintf(output, "%s = %s,\t &%s = %p", #VAR, hex_vals_var, #VAR, (void *) &VAR); \
			strcpy(info_msg->msg, output);			\
		} else {						\
			sprintf(output, "%s = %s,\t &%s = %p", #VAR, format, #VAR, (void *) &VAR); \
			sprintf(info_msg->msg, output, VAR);		\
		}							\
	} while (0)


#define INFO_EXPR(EXPR)				\
	do {					\
		UnitTestInfo    *info = &unitcase->info;		\
		UnitTestInfoMsg *info_msg =				\
			&info->info_msgs[info->number_info_msgs++];	\
		info_msg->test = unitframe.current_test;		\
		info_msg->line = __LINE__;				\
		const char *format = _UNITTEST_DTYPES_C_FORMAT((EXPR));	\
		char	    output[INFO_MSG_SIZE];			\
		sprintf(output, "(%s) ==> %s", #EXPR, format);		\
		sprintf(info_msg->msg, output, EXPR);			\
	} while (0)
	

typedef struct {
	const char *test;
	char msg[INFO_MSG_SIZE];
	int	    line;
} UnitTestInfoMsg;

typedef struct {
	const char	     *unitcase, *file;
	size_t		      number_failed_asserts;
	size_t number_info_msgs;
	size_t		      number_warning_expects;
	
	UnitTestAssertionInfo failed_asserts[MAX_AMOUNT_OF_FAILED_ASSERTIONS_IN_TESTCASE];
	UnitTestExpectatinoInfo warning_expects[MAX_AMOUNT_OF_FAILED_ASSERTIONS_IN_TESTCASE];
	UnitTestInfoMsg info_msgs[MAX_AMOUNT_OF_MSGS_IN_TESTS];
} UnitTestInfo;

extern UnitTestInfo *unittest_infotestcases[MAX_AMOUNT_OF_INFO_FAILES];

/* unittest_print_info_testcase: This function prints the information for the failures, wanrs and
   messages from a testcase. */
extern void unittest_print_info_testcase(const UnitTestInfo *unitcase);

#endif
