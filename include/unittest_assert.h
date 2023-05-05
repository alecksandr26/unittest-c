/*!
  @file unittest_assert.h
  @brief The assertions macros for the testcases.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_ASSERT_INCLUDE
#define UNITTEST_ASSERT_INCLUDE

#include "../include/unittest.h"
/* Sime implemention of an assert */
extern void unittest_print_fails(TestCase *tcase);
#define FIRST(X, ...) X
#define ASSERT(EXPR, ...)						\
	if (!(EXPR)) {							\
		tcase->failed_info[tcase->amount_failed].expr = #EXPR;	\
		tcase->failed_info[tcase->amount_failed].msg =		\
			FIRST(__VA_ARGS__ __VA_OPT__(,) NULL);		\
		tcase->failed_info[tcase->amount_failed].test =		\
			tframe.current_test;				\
		tcase->failed_info[tcase->amount_failed].line		\
			= __LINE__;					\
		tcase->amount_failed++;					\
		/* Stops executing the test and jump to execute more tests */ \
		putchar('F');						\
		jmpback(&tframe.buf, tframe.state + 1);			\
	}
#endif
