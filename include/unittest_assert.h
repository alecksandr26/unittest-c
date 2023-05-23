/*!
  @file unittest_assert.h
  @brief This component provides a simple yet powerful mechanism for verifying the correctness of
  code during testing, helping to improve code quality and reduce the risk of regressions.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_ASSERT_INCLUDE
#define UNITTEST_ASSERT_INCLUDE

#include <stdio.h>
#include "unittest_debug.h"

#define F UnitTestInfoFailed

/* The structure that captures all information needed for a failed test. */
typedef struct F F;
struct F {
	const char *expr, *msg, *test, *unitcase, *file;
	int	    line;
};

/* unittest_print_faild_test: This function prints the information for a failed test,
   including the expression, message, test name, testcase name and filename. */
extern void unittest_print_faild_test(F *unitcase);

#define UNITTEST_FIRST(X, ...) X

/* ASSERT: evaluates expression, records failed test info, increments failure count,
   outputs 'F',
   and jumps back to execute more tests using setjmp(). */
#define ASSERT(EXPR, ...)                                                       \
	if (!(EXPR)) {                                                          \
		unitcase->failed_info[unitcase->amount_failed].expr = #EXPR;    \
		unitcase->failed_info[unitcase->amount_failed].msg =            \
			UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL); \
		unitcase->failed_info[unitcase->amount_failed].test =           \
			unitframe.current_test;                                 \
		unitcase->failed_info[unitcase->amount_failed].line = __LINE__; \
		unitcase->amount_failed++;                                      \
		/* Stops executing the test and jump to execute more tests */   \
		LOG("F");						\
		jmpback(&unitframe.buf, unitframe.state + 1);                   \
	} else

#undef F
#endif
