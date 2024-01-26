/*!
  @file unittest_expect.h
  @brief This component provides a simple yet powerful mechanism for verifying the correctness of
  code during testing, helping to improve code quality and reduce the risk of regressions.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_EXPECT_INCLUDE
#define UNITTEST_EXPECT_INCLUDE

#include "unittest_def.h"
#include "unittest_debug.h"

#include <stdio.h>
#include <string.h>


/* EXPECT: Evaluates expression, records warning test info, increments warning count,
   outputs 'UnitTestInfoFailed', and continue executing the test. */
#define EXPECT(EXPR, ...)						\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestExpectatinoInfo *info_expect = &info->warning_expects[info->number_warning_expects]; \
		_UNITTEST_CATCH_INFO(info_expect, __LINE__,		\
				     _UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL), \
				   unitframe.current_test);		\
		if (!(EXPR)) {						\
			sprintf(info_expect->expr, "%s, which is false", #EXPR); \
			info->number_warning_expects++;			\
			unitcase->res = 'W';				\
		}							\
	} while (0)


/* EXPECT_EQ: Evaluate if the variables are equal,  records warning test info, increments warning count,
   outputs 'UnitTestInfoFailed', and continue executing the test. */
#define EXPECT_EQ(X, Y, ...)						\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestExpectatinoInfo *info_expect = &info->warning_expects[info->number_warning_expects]; \
		_UNITTEST_CATCH_INFO(info_expect, __LINE__,		\
				   _UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL), \
				   unitframe.current_test);		\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;					\
		if (memcmp((char *) &unittest_var1, (char *) &unittest_var2, sizeof(X))) { \
			_UNITTEST_CATCH_COMPARISON_INFO(info_expect, X, Y, unittest_var1, unittest_var2, "=="); \
			info->number_warning_expects++;			\
			unitcase->res = 'W';				\
		}							\
	} while (0)

/* EXPECT_NEQ: Evaluate if the variables are not equal,  records warning test info, increments warning count,
   outputs 'UnitTestInfoFailed', and continue executing the test. */
#define EXPECT_NEQ(X, Y, ...)						\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestExpectatinoInfo *info_expect = &info->warning_expects[info->number_warning_expects]; \
		_UNITTEST_CATCH_INFO(info_expect, __LINE__,		\
				   _UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL), \
				   unitframe.current_test);		\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;					\
		if (!memcmp((char *) &unittest_var1, (char *) &unittest_var2, sizeof(X))) { \
			_UNITTEST_CATCH_COMPARISON_INFO(info_expect, X, Y, unittest_var1, unittest_var2, "!="); \
			info->number_warning_expects++;			\
			unitcase->res = 'W';				\
		}							\
	} while (0)


/* EXPECT_LT: Evaluate if X is lesser than Y,  records warning test info, increments warning count,
   outputs 'UnitTestInfoFailed', and continue executing the test. */
#define EXPECT_LT(X, Y, ...)						\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestExpectatinoInfo *info_expect = &info->warning_expects[info->number_warning_expects]; \
		_UNITTEST_CATCH_INFO(info_expect, __LINE__,		\
				   _UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL), \
				   unitframe.current_test);		\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;					\
		if (0 <= memcmp((char *) &unittest_var1, (char *) &unittest_var2, sizeof(X))) { \
			_UNITTEST_CATCH_COMPARISON_INFO(info_expect, X, Y, unittest_var1, unittest_var2, "<"); \
			info->number_warning_expects++;			\
			unitcase->res = 'W';				\
		}							\
	} while (0)



/* EXPECT_LE: Evaluate if X is lesser than or equal Y,  records warning test info, increments warning count,
   outputs 'UnitTestInfoFailed', and continue executing the test. */
#define EXPECT_LE(X, Y, ...)						\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestExpectatinoInfo *info_expect = &info->warning_expects[info->number_warning_expects]; \
		_UNITTEST_CATCH_INFO(info_expect, __LINE__,		\
				   _UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL), \
				   unitframe.current_test);		\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;					\
		if (0 < memcmp((char *) &unittest_var1, (char *) &unittest_var2, sizeof(X))) { \
			_UNITTEST_CATCH_COMPARISON_INFO(info_expect, X, Y, unittest_var1, unittest_var2, "<="); \
			info->number_warning_expects++;			\
			unitcase->res = 'W';				\
		}							\
	} while (0)


/* EXPECT_GT: Evaluate if X is greater than Y,  records warning test info, increments warning count,
   outputs 'UnitTestInfoFailed', and continue executing the test. */
#define EXPECT_GT(X, Y, ...)						\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestExpectatinoInfo *info_expect = &info->warning_expects[info->number_warning_expects]; \
		_UNITTEST_CATCH_INFO(info_expect, __LINE__,		\
				   _UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL), \
				   unitframe.current_test);		\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;					\
		if (0 >= memcmp((char *) &unittest_var1, (char *) &unittest_var2, sizeof(X))) { \
			_UNITTEST_CATCH_COMPARISON_INFO(info_expect, X, Y, unittest_var1, unittest_var2, ">"); \
			info->number_warning_expects++;			\
			unitcase->res = 'W';				\
		}							\
	} while (0)

/* EXPECT_GE: Evaluate if X is greater than  or equal Y,  records warning test info, increments warning count,
   outputs 'UnitTestInfoFailed', and continue executing the test. */
#define EXPECT_GE(X, Y, ...)						\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestExpectatinoInfo *info_expect = &info->warning_expects[info->number_warning_expects]; \
		_UNITTEST_CATCH_INFO(info_expect, __LINE__,		\
				   _UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL), \
				   unitframe.current_test);		\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;					\
		if (0 > memcmp((char *) &unittest_var1, (char *) &unittest_var2, sizeof(X))) { \
			_UNITTEST_CATCH_COMPARISON_INFO(info_expect, X, Y, unittest_var1, unittest_var2, ">="); \
			info->number_warning_expects++;			\
			unitcase->res = 'W';				\
		}							\
	} while (0)


/* EXPECT_STR_EQ: Evaluate the equality of two strings (X and Y), if the strings are not equal,
   records warning test info.  */
#define EXPECT_STR_EQ(X, Y, ...)					\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestExpectatinoInfo *info_expect = &info->warning_expects[info->number_warning_expects]; \
		_UNITTEST_CATCH_INFO(info_expect, __LINE__,		\
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
			_UNITTEST_CATCH_COMPARISON_INFO(info_expect, X, Y, unittest_var1, unittest_var2, "=="); \
			info->number_warning_expects++;			\
			unitcase->res = 'W';				\
		}							\
	} while (0)


/* EXPECT_STR_NEQ: Evaluate the inequality of two strings (X and Y), if the strings are not equal,
   records warning test info.  */
#define EXPECT_STR_NEQ(X, Y, ...)					\
	do {								\
		UnitTestInfoFailed *info = &unitcase->failed_info;	\
		UnitTestExpectatinoInfo *info_expect = &info->warning_expects[info->number_warning_expects]; \
		_UNITTEST_CATCH_INFO(info_expect, __LINE__,		\
				     _UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL), \
				     unitframe.current_test);		\
		char unittest_var1[UNITTEST_STR_SIZE];			\
		memset(unittest_var1, 0, UNITTEST_STR_SIZE);		\
		memcpy(unittest_var1, X, strlen(X));			\
		char unittest_var2[UNITTEST_STR_SIZE];			\
		memset(unittest_var2, 0, UNITTEST_STR_SIZE);		\
		memcpy(unittest_var2, Y, strlen(Y));			\
		if (strlen(X) != strlen(Y)				\
		    || !memcmp(unittest_var1, unittest_var2, strlen(X))) { \
			_UNITTEST_CATCH_COMPARISON_INFO(info_expect, X, Y, unittest_var1, unittest_var2, "!="); \
			info->number_warning_expects++;			\
			unitcase->res = 'W';				\
		}							\
	} while (0)


/* The structure that captures all information needed for a warning expect test. */
typedef struct {
	const char *msg, *test;
	char expr[EXPR_LENGHT_SIZE];
	int line;
} UnitTestExpectatinoInfo;

#endif



