/*!
  @file unittest_tcase.h
  @brief defines the structures and functions necessary for creating and running test cases in for this
  unit testing framework. It includes structures to keep track of test cases and their individual tests,
  as well as macros for defining test cases, individual tests, and ending test cases.
  The file also defines a function for linking together multiple test cases.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_TESTCASE_INCLUDED
#define UNITTEST_TESTCASE_INCLUDED

#include "unittest_assert.h"

#include <assert.h>
#include <except.h>
#include <stddef.h>

#define F				 UnitTestInfoFailed
#define TC				 UnitTestCase
#define TF				 UnitTestCaseFrame
#define MAX_AMOUNT_OF_TESTS_IN_TESTCASES 1024

/* The TC struct represents a test case and includes information such as file name, test
   name,
   test function, and an array of failed test info. */
typedef struct TC TC;
struct TC {
	const char *file, *name;
	size_t	    amount, amount_failed;
	TC	   *next;

	/* Catch the test function */
	void (*test)(TC *);
	F failed_info[MAX_AMOUNT_OF_TESTS_IN_TESTCASES];
};

/* The TF structure is a data structure that contains information about the state of a
 * test case. */
typedef struct TF TF;
struct TF {
	volatile int state;
	const char  *current_test;
	int	     counter;
	JmpBuf	     buf;
};

/* These are macros used to define and run test cases. */
#define TestCase(TEST_CASE_NAME)                                                     \
	void	     TestCase##TEST_CASE_NAME(UnitTestCase *unitcase);               \
	UnitTestCase TEST_CASE_NAME = {.file	      = __FILE__,                    \
				       .name	      = #TEST_CASE_NAME,             \
				       .amount	      = 0,                           \
				       .amount_failed = 0,                           \
				       .next	      = NULL,                        \
				       .test	      = &(TestCase##TEST_CASE_NAME), \
				       .failed_info   = {{0}}};                        \
	void	     TestCase##TEST_CASE_NAME(UnitTestCase *unitcase)                \
	{                                                                            \
		assert(unitcase != NULL && "Can't be null unitcase tests");          \
		UnitTestCaseFrame unitframe;                                         \
		unitframe.state	  = stackjmp(&unitframe.buf);                        \
		unitframe.counter = 0;                                               \
		do

#define Test(TEST_NAME)                               \
	unitframe.current_test = #TEST_NAME;          \
	/* Count all the tests */                     \
	if (unitframe.state == 0) unitcase->amount++; \
	if (unitframe.state == ++unitframe.counter)

#define EndTestCase                                                                  \
	while (0)                                                                    \
		;                                                                    \
	assert(unitcase->amount > 0 && "The testcase should have atleast one test"); \
	if (unitframe.state > 0 && unitframe.state <= (int) unitcase->amount)        \
		putchar('.');                                                        \
	if (unitframe.state < (int) unitcase->amount)                                \
		jmpback(&unitframe.buf, unitframe.state + 1);                        \
	}

/* unittest_head_tc: A pointer to the last linked test case. */
extern TC *unittest_head_tc;

/* link_tcases: Links test case structures together for the testing process. */
extern void unittest_link_tcase(TC *unitcase);

#undef F
#undef TC
#undef TF
#endif
