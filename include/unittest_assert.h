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

#define F TestInfoFailed

/* The structure that captures all information needed for a failed test. */
typedef struct F F;
struct F {
	const char *expr, *msg, *test, *tcase, *file;
	int	    line;
};

/* unittest_print_faild_test: This function prints the information for a failed test,
   including the expression, message, test name, testcase name and filename. */
extern void unittest_print_faild_test(F *tcase);

#define FIRST(X, ...) X

/* ASSERT: evaluates expression, records failed test info, increments failure count,
   outputs 'F',
   and jumps back to execute more tests using setjmp(). */
#define ASSERT(EXPR, ...)                                                            \
	if (!(EXPR)) {                                                               \
		tcase->failed_info[tcase->amount_failed].expr = #EXPR;               \
		tcase->failed_info[tcase->amount_failed].msg =                       \
			FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL);                      \
		tcase->failed_info[tcase->amount_failed].test = tframe.current_test; \
		tcase->failed_info[tcase->amount_failed].line = __LINE__;            \
		tcase->amount_failed++;                                              \
		/* Stops executing the test and jump to execute more tests */ \
		putchar('F');						\
		jmpback(&tframe.buf, tframe.state + 1);			\
	} else 

#undef F
#endif
