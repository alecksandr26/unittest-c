/*!
  @file unittest_infofail.h
  @brief 

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_INFOFAIL_INCLUDE
#define UNITTEST_INFOFAIL_INCLUDE


#include "unittest_def.h"
#include "unittest_debug.h"
#include "unittest_assert.h"
#include "unittest_expect.h"

#include <string.h>

#define _UNITTEST_UNKNOWN_DTYPE "unknown"

#define _UNITTEST_DTYPES_C_FORMAT(X) _Generic((X),			\
					      int:    "%i",		\
					      long:    "%li",		\
					      short:    "%hi",		\
					      unsigned:   "%u",		\
					      unsigned long:    "%lu",	\
					      unsigned short:   "%hu",	\
					      double: "%lf",		\
					      float: "%f",		\
					      char:   "%c",		\
					      char *:   "%s",		\
					      default: _UNITTEST_UNKNOWN_DTYPE \
					      )


#define _UNITTEST_FIRST(X, ...) X

#define _UNITTEST_CATCH_INFO(INFO, LINE, MSG, TEST)	\
	do {						\
		(INFO)->line = LINE;			\
		(INFO)->msg = MSG;			\
		(INFO)->test = TEST;			\
	} while (0)


#define _UNITTEST_CATCH_COMPARISON_INFO(INFO, X, Y, VAR1, VAR2, COMP)	\
	do {								\
		char output_expr[ERROR_INFO_MSG_SIZE];			\
		const char *format = _UNITTEST_DTYPES_C_FORMAT(X);	\
		if (strcmp(format, _UNITTEST_UNKNOWN_DTYPE) == 0) {	\
			size_t n = (sizeof(unittest_var1) < 5) ? sizeof(unittest_var1) : 5; \
			size_t nb = n * 2 + 1;				\
			char hex_vals_var1[nb];				\
			char hex_vals_var2[nb];				\
			capture_n_hexvals(((char *) &VAR1), n, hex_vals_var1, nb); \
			capture_n_hexvals(((char *) &VAR2), n, hex_vals_var2, nb); \
			sprintf(output_expr,				\
				"%s %s %s, where %s = 0X%s... and %s = 0X%s... " \
				"have unknown data types",		\
				#X, COMP, #Y, #X, hex_vals_var1, #Y, hex_vals_var2); \
			strcpy(INFO->expr, output_expr);		\
		} else {						\
			sprintf(output_expr, "%s %s %s, where %s = %s and %s = %s", \
				#X, COMP, #Y, #X, format, #Y, format);	\
			sprintf(INFO->expr, output_expr, X, Y);	\
		}							\
	} while (0)


typedef struct {
	const char *unitcase, *file;
	size_t number_failed_asserts;
	UnitTestAssertionInfo failed_asserts[MAX_AMOUNT_OF_FAILED_ASSERTIONS_IN_TESTCASE];
	size_t number_warning_expects;
	UnitTestExpectatinoInfo warning_expects[MAX_AMOUNT_OF_FAILED_ASSERTIONS_IN_TESTCASE];
} UnitTestInfoFailed;

extern UnitTestInfoFailed *infofails[MAX_AMOUNT_OF_INFO_FAILES];

/* unittest_print_faild_testcase: This function prints the information for the failures from a testcase,
   including the expressions, messages, test names, testcase name and filename. */
extern void unittest_print_faild_testcase(UnitTestInfoFailed *unitcase);

#endif




