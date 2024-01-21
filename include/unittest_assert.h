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

#define _UNITTEST_UNSUPPOERTED_DTYPE "Unsupported data type"

#define _UNITTEST_DTYPES_C_FORMAT(x) _Generic((x),				\
					      int:    "%i",		\
					      long:    "%li",		\
					      short:    "%hi",		\
					      unsigned:   "%u",		\
					      unsigned long:    "%lu",	\
					      unsigned short:   "%hu",	\
					      double: "%lf",		\
					      float: "%f",		\
					      char:   "%c",		\
					      default: _UNITTEST_UNSUPPOERTED_DTYPE \
					      )


#define _UNITTEST_FIRST(X, ...) X

/* ASSERT: Evaluates expression, records failed test info, increments failure count,
   outputs 'UnitTestInfoFailed', and jumps back to execute more tests using setjmp(). */
#define ASSERT(EXPR, ...)						\
	do {								\
		char *ptr_expr = unitcase->failed_info[unitcase->amount_failed].expr; \
		if (!(EXPR)) {						\
			memset(ptr_expr, 0, EXPR_LENGHT_SIZE);		\
			sprintf(ptr_expr, "%s, which is false", #EXPR); \
			unitcase->failed_info[unitcase->amount_failed].msg = \
				_UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL); \
			unitcase->failed_info[unitcase->amount_failed].test = \
				unitframe.current_test;			\
			unitcase->failed_info[unitcase->amount_failed].line = __LINE__; \
			unitcase->amount_failed++;			\
			/* Stops executing the test and jump to execute more tests */ \
			LOG("F");					\
			jmpback(&unitframe.buf, unitframe.state + 1);	\
		}							\
	} while (0)



/* ASSERT_EQ: Evaluate if the variables are equal, records info in the case if they weren't
   equal and counts this test as failed and continue testing other tests. */
#define ASSERT_EQ(X, Y, ...)						\
	do {								\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;				\
		char *ptr_expr = unitcase->failed_info[unitcase->amount_failed].expr; \
		size_t unittest_index = unittest_memory_cmp((char *) &unittest_var1, \
							    (char *) &unittest_var2, sizeof(unittest_var1)); \
		if (unittest_index < sizeof(unittest_var1)) {		\
			char output_expr[ERROR_INFO_MSG_SIZE];		\
			memset(output_expr, 0, ERROR_INFO_MSG_SIZE);	\
			memset(ptr_expr, 0, EXPR_LENGHT_SIZE);		\
			char *format_var1 = _UNITTEST_DTYPES_C_FORMAT(unittest_var1); \
			char *format_var2 = _UNITTEST_DTYPES_C_FORMAT(unittest_var2); \
			if (strcmp(format_var1, _UNITTEST_UNSUPPOERTED_DTYPE) == 0) { \
				size_t n = sizeof(unittest_var1) - unittest_index; \
				n = (n < 5) ? n : 5;			\
				size_t nb = n * 2 + 1;			\
				char hex_vals_var1[nb];			\
				char hex_vals_var2[nb];			\
				memset(hex_vals_var1, 0, nb);		\
				memset(hex_vals_var2, 0, nb);		\
				capture_n_hexvals(((char *) &unittest_var1) + unittest_index, n, \
						  hex_vals_var1, nb);	\
				capture_n_hexvals(((char *) &unittest_var2) + unittest_index, n, \
						  hex_vals_var2, nb);	\
				sprintf(output_expr, "%s == %s, where %s = %s%s%s and %s = %s%s%s", \
					#X, #Y, #X,			\
					(unittest_index > 0) ? "0x..." : "0x", hex_vals_var1, \
					(unittest_index < sizeof(unittest_var1) - n) ? "..." : "", \
					#Y,				\
					(unittest_index > 0) ? "0x..." : "0x", hex_vals_var2, \
					(unittest_index < sizeof(unittest_var1) - n) ? "..." : ""); \
				strcpy(ptr_expr, output_expr);		\
			} else {					\
				sprintf(output_expr, "%s == %s, where %s = %s and %s = %s", #X, #Y, \
					#X, format_var1, #Y, format_var2); \
				sprintf(ptr_expr, output_expr, X, Y);	\
			}						\
			unitcase->failed_info[unitcase->amount_failed].msg = \
				_UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL); \
			unitcase->failed_info[unitcase->amount_failed].test = \
				unitframe.current_test;			\
			unitcase->failed_info[unitcase->amount_failed].line = __LINE__; \
			unitcase->amount_failed++;			\
			/* Stops executing the test and jump to execute more tests */ \
			LOG("F");					\
			jmpback(&unitframe.buf, unitframe.state + 1);	\
		}							\
	} while (0)


/* ASSERT_NEQ: Evaluate if the variables are not equal, records info in the case if they weren't
   equal and counts this test as failed and continue testing other tests. */
#define ASSERT_NEQ(X, Y, ...)						\
	do {								\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;				\
		char *ptr_expr = unitcase->failed_info[unitcase->amount_failed].expr; \
		size_t unittest_index = unittest_memory_cmp((char *) &unittest_var1, \
							    (char *) &unittest_var2, sizeof(unittest_var1)); \
		if (!(unittest_index < sizeof(unittest_var1))) {	\
			char output_expr[ERROR_INFO_MSG_SIZE];		\
			memset(output_expr, 0, ERROR_INFO_MSG_SIZE);	\
			memset(ptr_expr, 0, EXPR_LENGHT_SIZE);		\
			char *format_var1 = _UNITTEST_DTYPES_C_FORMAT(unittest_var1); \
			char *format_var2 = _UNITTEST_DTYPES_C_FORMAT(unittest_var2); \
			if (strcmp(format_var1, _UNITTEST_UNSUPPOERTED_DTYPE) == 0) { \
				size_t n = (sizeof(unittest_var1) < 5) ? sizeof(unittest_var1) : 5; \
				size_t nb = n * 2 + 1;			\
				char hex_vals_var1[nb];			\
				char hex_vals_var2[nb];			\
				memset(hex_vals_var1, 0, nb);		\
				memset(hex_vals_var2, 0, nb);		\
				capture_n_hexvals(((char *) &unittest_var1), n, \
						  hex_vals_var1, nb);	\
				capture_n_hexvals(((char *) &unittest_var2), n, \
						  hex_vals_var2, nb);	\
				sprintf(output_expr, "%s != %s, where %s = %s%s%s and %s = %s%s%s", \
					#X, #Y, #X,			\
					"0x", hex_vals_var1,		\
					(n < sizeof(unittest_var1)) ? "..." : "", \
					#Y,				\
					"0x", hex_vals_var2,		\
					(n < sizeof(unittest_var1)) ? "..." : ""); \
				strcpy(ptr_expr, output_expr);		\
			} else {					\
				sprintf(output_expr, "%s != %s, where %s = %s and %s = %s", #X, #Y, \
					#X, format_var1, #Y, format_var2); \
				sprintf(ptr_expr, output_expr, X, Y);	\
			}						\
			unitcase->failed_info[unitcase->amount_failed].msg = \
				_UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL); \
			unitcase->failed_info[unitcase->amount_failed].test = \
				unitframe.current_test;			\
			unitcase->failed_info[unitcase->amount_failed].line = __LINE__; \
			unitcase->amount_failed++;			\
			/* Stops executing the test and jump to execute more tests */ \
			LOG("F");					\
			jmpback(&unitframe.buf, unitframe.state + 1);	\
		}							\
	} while (0)

/* ASSERT_LT: Evaluate if X is lesser than Y, records info in the case if they weren't
   equal and counts this test as failed and continue testing other tests.  */
#define ASSERT_LT(X, Y, ...)						\
	do {								\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;				\
		char *ptr_expr = unitcase->failed_info[unitcase->amount_failed].expr; \
		int cmp = memcmp((char *) &unittest_var1,		\
				 (char *) &unittest_var2, sizeof(unittest_var1)); \
		if (0 <= cmp) {						\
			char output_expr[ERROR_INFO_MSG_SIZE];		\
			memset(output_expr, 0, ERROR_INFO_MSG_SIZE);	\
			memset(ptr_expr, 0, EXPR_LENGHT_SIZE);		\
			char *format_var1 = _UNITTEST_DTYPES_C_FORMAT(unittest_var1); \
			char *format_var2 = _UNITTEST_DTYPES_C_FORMAT(unittest_var2); \
			if (strcmp(format_var1, _UNITTEST_UNSUPPOERTED_DTYPE) == 0) { \
				size_t n = (sizeof(unittest_var1) < 5) ? sizeof(unittest_var1) : 5; \
				size_t nb = n * 2 + 1;			\
				char hex_vals_var1[nb];			\
				char hex_vals_var2[nb];			\
				memset(hex_vals_var1, 0, nb);		\
				memset(hex_vals_var2, 0, nb);		\
				capture_n_hexvals(((char *) &unittest_var1), n, \
						  hex_vals_var1, nb);	\
				capture_n_hexvals(((char *) &unittest_var2), n, \
						  hex_vals_var2, nb);	\
				sprintf(output_expr, "%s < %s, where %s = %s%s%s and %s = %s%s%s", \
					#X, #Y, #X,			\
					"0x", hex_vals_var1,		\
					(n < sizeof(unittest_var1)) ? "..." : "", \
					#Y,				\
					"0x", hex_vals_var2,		\
					(n < sizeof(unittest_var1)) ? "..." : ""); \
				strcpy(ptr_expr, output_expr);		\
			} else {					\
				sprintf(output_expr, "%s < %s, where %s = %s and %s = %s", #X, #Y, \
					#X, format_var1, #Y, format_var2); \
				sprintf(ptr_expr, output_expr, X, Y);	\
			}						\
			unitcase->failed_info[unitcase->amount_failed].msg = \
				_UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL); \
			unitcase->failed_info[unitcase->amount_failed].test = \
				unitframe.current_test;			\
			unitcase->failed_info[unitcase->amount_failed].line = __LINE__; \
			unitcase->amount_failed++;			\
			/* Stops executing the test and jump to execute more tests */ \
			LOG("F");					\
			jmpback(&unitframe.buf, unitframe.state + 1);	\
		}							\
	} while (0)


/* ASSERT_LE: Evaluate if X is lesser than or equal Y, records info in the case if they weren't
   equal and counts this test as failed and continue testing other tests.  */
#define ASSERT_LE(X, Y, ...)						\
	do {								\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;				\
		char *ptr_expr = unitcase->failed_info[unitcase->amount_failed].expr; \
		int cmp = memcmp((char *) &unittest_var1,		\
				 (char *) &unittest_var2, sizeof(unittest_var1)); \
		if (0 < cmp) {						\
			char output_expr[ERROR_INFO_MSG_SIZE];		\
			memset(output_expr, 0, ERROR_INFO_MSG_SIZE);	\
			memset(ptr_expr, 0, EXPR_LENGHT_SIZE);		\
			char *format_var1 = _UNITTEST_DTYPES_C_FORMAT(unittest_var1); \
			char *format_var2 = _UNITTEST_DTYPES_C_FORMAT(unittest_var2); \
			if (strcmp(format_var1, _UNITTEST_UNSUPPOERTED_DTYPE) == 0) { \
				size_t n = (sizeof(unittest_var1) < 5) ? sizeof(unittest_var1) : 5; \
				size_t nb = n * 2 + 1;			\
				char hex_vals_var1[nb];			\
				char hex_vals_var2[nb];			\
				memset(hex_vals_var1, 0, nb);		\
				memset(hex_vals_var2, 0, nb);		\
				capture_n_hexvals(((char *) &unittest_var1), n, \
						  hex_vals_var1, nb);	\
				capture_n_hexvals(((char *) &unittest_var2), n, \
						  hex_vals_var2, nb);	\
				sprintf(output_expr, "%s <= %s, where %s = %s%s%s and %s = %s%s%s", \
					#X, #Y, #X,			\
					"0x", hex_vals_var1,		\
					(n < sizeof(unittest_var1)) ? "..." : "", \
					#Y,				\
					"0x", hex_vals_var2,		\
					(n < sizeof(unittest_var1)) ? "..." : ""); \
				strcpy(ptr_expr, output_expr);		\
			} else {					\
				sprintf(output_expr, "%s <= %s, where %s = %s and %s = %s", #X, #Y, \
					#X, format_var1, #Y, format_var2); \
				sprintf(ptr_expr, output_expr, X, Y);	\
			}						\
			unitcase->failed_info[unitcase->amount_failed].msg = \
				_UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL); \
			unitcase->failed_info[unitcase->amount_failed].test = \
				unitframe.current_test;			\
			unitcase->failed_info[unitcase->amount_failed].line = __LINE__; \
			unitcase->amount_failed++;			\
			/* Stops executing the test and jump to execute more tests */ \
			LOG("F");					\
			jmpback(&unitframe.buf, unitframe.state + 1);	\
		}							\
	} while (0)

/* ASSERT_GT: Evaluate if X is greater than Y, records info in the case if they weren't
   equal and counts this test as failed and continue testing other tests.  */
#define ASSERT_GT(X, Y, ...)						\
	do {								\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;				\
		char *ptr_expr = unitcase->failed_info[unitcase->amount_failed].expr; \
		int cmp = memcmp((char *) &unittest_var1,		\
				 (char *) &unittest_var2, sizeof(unittest_var1)); \
		if (cmp <= 0) {						\
			char output_expr[ERROR_INFO_MSG_SIZE];		\
			memset(output_expr, 0, ERROR_INFO_MSG_SIZE);	\
			memset(ptr_expr, 0, EXPR_LENGHT_SIZE);		\
			char *format_var1 = _UNITTEST_DTYPES_C_FORMAT(unittest_var1); \
			char *format_var2 = _UNITTEST_DTYPES_C_FORMAT(unittest_var2); \
			if (strcmp(format_var1, _UNITTEST_UNSUPPOERTED_DTYPE) == 0) { \
				size_t n = (sizeof(unittest_var1) < 5) ? sizeof(unittest_var1) : 5; \
				size_t nb = n * 2 + 1;			\
				char hex_vals_var1[nb];			\
				char hex_vals_var2[nb];			\
				memset(hex_vals_var1, 0, nb);		\
				memset(hex_vals_var2, 0, nb);		\
				capture_n_hexvals(((char *) &unittest_var1), n, \
						  hex_vals_var1, nb);	\
				capture_n_hexvals(((char *) &unittest_var2), n, \
						  hex_vals_var2, nb);	\
				sprintf(output_expr, "%s > %s, where %s = %s%s%s and %s = %s%s%s", \
					#X, #Y, #X,			\
					"0x", hex_vals_var1,		\
					(n < sizeof(unittest_var1)) ? "..." : "", \
					#Y,				\
					"0x", hex_vals_var2,		\
					(n < sizeof(unittest_var1)) ? "..." : ""); \
				strcpy(ptr_expr, output_expr);		\
			} else {					\
				sprintf(output_expr, "%s > %s, where %s = %s and %s = %s", #X, #Y, \
					#X, format_var1, #Y, format_var2); \
				sprintf(ptr_expr, output_expr, X, Y);	\
			}						\
			unitcase->failed_info[unitcase->amount_failed].msg = \
				_UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL); \
			unitcase->failed_info[unitcase->amount_failed].test = \
				unitframe.current_test;			\
			unitcase->failed_info[unitcase->amount_failed].line = __LINE__; \
			unitcase->amount_failed++;			\
			/* Stops executing the test and jump to execute more tests */ \
			LOG("F");					\
			jmpback(&unitframe.buf, unitframe.state + 1);	\
		}							\
	} while (0)


/* ASSERT_GE: Evaluate if X is greater than or equal Y, records info in the case if they weren't
   equal and counts this test as failed and continue testing other tests.  */
#define ASSERT_GE(X, Y, ...)						\
	do {								\
		typeof(X) unittest_var1 = X;				\
		typeof(X) unittest_var2 = Y;				\
		char *ptr_expr = unitcase->failed_info[unitcase->amount_failed].expr; \
		int cmp = memcmp((char *) &unittest_var1,		\
				 (char *) &unittest_var2, sizeof(unittest_var1)); \
		if (cmp < 0) {						\
			char output_expr[ERROR_INFO_MSG_SIZE];		\
			memset(output_expr, 0, ERROR_INFO_MSG_SIZE);	\
			memset(ptr_expr, 0, EXPR_LENGHT_SIZE);		\
			char *format_var1 = _UNITTEST_DTYPES_C_FORMAT(unittest_var1); \
			char *format_var2 = _UNITTEST_DTYPES_C_FORMAT(unittest_var2); \
			if (strcmp(format_var1, _UNITTEST_UNSUPPOERTED_DTYPE) == 0) { \
				size_t n = (sizeof(unittest_var1) < 5) ? sizeof(unittest_var1) : 5; \
				size_t nb = n * 2 + 1;			\
				char hex_vals_var1[nb];			\
				char hex_vals_var2[nb];			\
				memset(hex_vals_var1, 0, nb);		\
				memset(hex_vals_var2, 0, nb);		\
				capture_n_hexvals(((char *) &unittest_var1), n, \
						  hex_vals_var1, nb);	\
				capture_n_hexvals(((char *) &unittest_var2), n, \
						  hex_vals_var2, nb);	\
				sprintf(output_expr, "%s >= %s, where %s = %s%s%s and %s = %s%s%s", \
					#X, #Y, #X,			\
					"0x", hex_vals_var1,		\
					(n < sizeof(unittest_var1)) ? "..." : "", \
					#Y,				\
					"0x", hex_vals_var2,		\
					(n < sizeof(unittest_var1)) ? "..." : ""); \
				strcpy(ptr_expr, output_expr);		\
			} else {					\
				sprintf(output_expr, "%s >= %s, where %s = %s and %s = %s", #X, #Y, \
					#X, format_var1, #Y, format_var2); \
				sprintf(ptr_expr, output_expr, X, Y);	\
			}						\
			unitcase->failed_info[unitcase->amount_failed].msg = \
				_UNITTEST_FIRST(__VA_ARGS__ __VA_OPT__(, ) NULL); \
			unitcase->failed_info[unitcase->amount_failed].test = \
				unitframe.current_test;			\
			unitcase->failed_info[unitcase->amount_failed].line = __LINE__; \
			unitcase->amount_failed++;			\
			/* Stops executing the test and jump to execute more tests */ \
			LOG("F");					\
			jmpback(&unitframe.buf, unitframe.state + 1);	\
		}							\
	} while (0)


/* The structure that captures all information needed for a failed test. */
typedef struct {
	const char *msg, *test, *unitcase, *file;
	char expr[EXPR_LENGHT_SIZE];
	int	    line;
} UnitTestInfoFailed;

extern UnitTestInfoFailed *infofails[MAX_AMOUNT_OF_TESTS_INFO_FAILD];

/* unittest_print_faild_test: This function prints the information for a failed test,
   including the expression, message, test name, testcase name and filename. */
extern void unittest_print_faild_test(UnitTestInfoFailed *unitcase);

#endif
