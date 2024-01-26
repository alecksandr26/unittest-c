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

#include "unittest_def.h"
#include "unittest_debug.h"

#include <stdio.h>
#include <string.h>

/* ASSERT: Evaluates expression, records failed test info, increments failure count,
   outputs 'UnitTestInfoFailed', and jumps back to execute more tests using setjmp(). */
#define ASSERT(EXPR, ...)						\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestAssertionInfo *info_assert = &info->failed_asserts[info->number_failed_asserts]; \
		_UNITTEST_CATCH_INFO(info_assert, __LINE__,		\
				     _UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL), \
				     unitframe.current_test);		\
		if (!(EXPR)) {						\
			sprintf(info_assert->expr, "%s, which is false", #EXPR); \
			info->number_failed_asserts++;			\
			unitcase->res = 'F';				\
			jmpback(&unitframe.buf, unitframe.state + 1);	\
		}							\
	} while (0)

/* ASSERT_EQ: Evaluate if the variables are equal, records info in the case if they weren't
   equal and counts this test as failed and continue testing other tests. */
#define ASSERT_EQ(X, Y, ...)						\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestAssertionInfo *info_assert = &info->failed_asserts[info->number_failed_asserts]; \
		_UNITTEST_CATCH_INFO(info_assert, __LINE__,		\
				   _UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL), \
				   unitframe.current_test);		\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;					\
		if (memcmp((char *) &unittest_var1, (char *) &unittest_var2, sizeof(X))) { \
			_UNITTEST_CATCH_COMPARISON_INFO(info_assert, X, Y, unittest_var1, unittest_var2, "=="); \
			info->number_failed_asserts++;			\
			unitcase->res = 'F';				\
			jmpback(&unitframe.buf, unitframe.state + 1);	\
		}							\
	} while (0)


/* ASSERT_NEQ: Evaluate if the variables are not equal, records info in the case if they weren't
   equal and counts this test as failed and continue testing other tests. */
#define ASSERT_NEQ(X, Y, ...)						\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestAssertionInfo *info_assert = &info->failed_asserts[info->number_failed_asserts]; \
		_UNITTEST_CATCH_INFO(info_assert, __LINE__,		\
				   _UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL), \
				   unitframe.current_test);		\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;				\
		if (!memcmp((char *) &unittest_var1, (char *) &unittest_var2, sizeof(X))) { \
			_UNITTEST_CATCH_COMPARISON_INFO(info_assert, X, Y, unittest_var1, unittest_var2, "!="); \
			info->number_failed_asserts++;			\
			unitcase->res = 'F';				\
			jmpback(&unitframe.buf, unitframe.state + 1);	\
		}							\
	} while (0)

/* ASSERT_LT: Evaluate if X is lesser than Y, records info in the case if they weren't
   equal and counts this test as failed and continue testing other tests.  */
#define ASSERT_LT(X, Y, ...)						\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestAssertionInfo *info_assert = &info->failed_asserts[info->number_failed_asserts]; \
		_UNITTEST_CATCH_INFO(info_assert, __LINE__,		\
				   _UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL), \
				   unitframe.current_test);		\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;				\
		if (0 <= memcmp((char *) &unittest_var1, (char *) &unittest_var2, sizeof(X))) { \
			_UNITTEST_CATCH_COMPARISON_INFO(info_assert, X, Y, unittest_var1, unittest_var2, "<"); \
			info->number_failed_asserts++;			\
			unitcase->res = 'F';				\
			jmpback(&unitframe.buf, unitframe.state + 1);	\
		}							\
	} while (0)


/* ASSERT_LE: Evaluate if X is lesser than or equal Y, records info in the case if they weren't
   equal and counts this test as failed and continue testing other tests.  */
#define ASSERT_LE(X, Y, ...)						\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestAssertionInfo *info_assert = &info->failed_asserts[info->number_failed_asserts]; \
		_UNITTEST_CATCH_INFO(info_assert, __LINE__,		\
				   _UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL), \
				   unitframe.current_test);		\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;				\
		if (0 < memcmp((char *) &unittest_var1, (char *) &unittest_var2, sizeof(X))) { \
			_UNITTEST_CATCH_COMPARISON_INFO(info_assert, X, Y, unittest_var1, unittest_var2, "<="); \
			info->number_failed_asserts++;			\
			unitcase->res = 'F';				\
			jmpback(&unitframe.buf, unitframe.state + 1);	\
		}							\
	} while (0)

/* ASSERT_GT: Evaluate if X is greater than Y, records info in the case if they weren't
   equal and counts this test as failed and continue testing other tests.  */
#define ASSERT_GT(X, Y, ...)						\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestAssertionInfo *info_assert = &info->failed_asserts[info->number_failed_asserts]; \
		_UNITTEST_CATCH_INFO(info_assert, __LINE__,		\
				   _UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL), \
				   unitframe.current_test);		\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;				\
		if (0 >= memcmp((char *) &unittest_var1, (char *) &unittest_var2, sizeof(X))) { \
			_UNITTEST_CATCH_COMPARISON_INFO(info_assert, X, Y, unittest_var1, unittest_var2, ">"); \
			info->number_failed_asserts++;			\
			unitcase->res = 'F';				\
			jmpback(&unitframe.buf, unitframe.state + 1);	\
		}							\
	} while (0)


/* ASSERT_GE: Evaluate if X is greater than or equal Y, records info in the case if they weren't
   equal and counts this test as failed and continue testing other tests.  */
#define ASSERT_GE(X, Y, ...)						\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestAssertionInfo *info_assert = &info->failed_asserts[info->number_failed_asserts]; \
		_UNITTEST_CATCH_INFO(info_assert, __LINE__,		\
				   _UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL), \
				   unitframe.current_test);		\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;				\
		if (0 > memcmp((char *) &unittest_var1, (char *) &unittest_var2, sizeof(X))) { \
			_UNITTEST_CATCH_COMPARISON_INFO(info_assert, X, Y, unittest_var1, unittest_var2, ">="); \
			info->number_failed_asserts++;			\
			unitcase->res = 'F';				\
			jmpback(&unitframe.buf, unitframe.state + 1);	\
		}							\
	} while (0)

/* ASSERT_STR_EQ: Asserts the equality of two strings (X and Y), if the strings are not equal,
   an assertion failure is triggered.  */
#define ASSERT_STR_EQ(X, Y, ...)					\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestAssertionInfo *info_assert = &info->failed_asserts[info->number_failed_asserts]; \
		_UNITTEST_CATCH_INFO(info_assert, __LINE__,		\
				   _UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL), \
				   unitframe.current_test);		\
		char unittest_var1[UNITTEST_STR_SIZE];			\
		memset(unittest_var1, 0, UNITTEST_STR_SIZE);		\
		memcpy(unittest_var1, X, strlen(X));			\
		char unittest_var2[UNITTEST_STR_SIZE];			\
		memset(unittest_var2, 0, UNITTEST_STR_SIZE);		\
		memcpy(unittest_var2, Y, strlen(Y));			\
		if (strlen(X) != strlen(Y)				\
		    || memcmp(unittest_var1, unittest_var2, strlen(X))) { \
			_UNITTEST_CATCH_COMPARISON_INFO(info_assert, X, Y, unittest_var1, unittest_var2, "=="); \
			info->number_failed_asserts++;			\
			unitcase->res = 'F';				\
			jmpback(&unitframe.buf, unitframe.state + 1);	\
		}							\
	} while (0)


/* ASSERT_STR_NEQ: Asserts the inequality of two strings (X and Y), if the strings are equal,
   an assertion failure is triggered. */
#define ASSERT_STR_NEQ(X, Y, ...)					\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestAssertionInfo *info_assert = &info->failed_asserts[info->number_failed_asserts]; \
		_UNITTEST_CATCH_INFO(info_assert, __LINE__,		\
				   _UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL), \
				   unitframe.current_test);		\
		char unittest_var1[UNITTEST_STR_SIZE];			\
		memset(unittest_var1, 0, UNITTEST_STR_SIZE);		\
		memcpy(unittest_var1, X, strlen(X));			\
		char unittest_var2[UNITTEST_STR_SIZE];			\
		memset(unittest_var2, 0, UNITTEST_STR_SIZE);		\
		memcpy(unittest_var2, Y, strlen(Y));			\
		if (strlen(X) == strlen(Y)				\
		    || !memcmp(unittest_var1, unittest_var2, strlen(X))) { \
			_UNITTEST_CATCH_COMPARISON_INFO(info_assert, X, Y, unittest_var1, unittest_var2, "!="); \
			info->number_failed_asserts++;			\
			unitcase->res = 'F';				\
			jmpback(&unitframe.buf, unitframe.state + 1);	\
		}							\
	} while (0)
	

/* The structure that captures all information needed for a failed assertion test. */
typedef struct {
	const char *msg, *test;
	char expr[EXPR_LENGHT_SIZE];
	int line;
} UnitTestAssertionInfo;

#endif
