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

#define F				 TestInfoFailed
#define TC				 TestCase
#define TF				 TestCaseFrame
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
	JmpBuf buf;
};

/* These are macros used to define and run test cases. */
#define TestCase(TEST_CASE_NAME)					\
	void	 TestCase##TEST_CASE_NAME(TestCase *tcase);			\
	TestCase TEST_CASE_NAME = {.file	  = __FILE__,		\
					   .name	  = #TEST_CASE_NAME, \
					   .amount	  = 0,		\
					   .amount_failed = 0,		\
					   .next	  = NULL,	\
					   .test	  = &(TestCase##TEST_CASE_NAME), \
					   .failed_info	  = {{0}}};	\
	void TestCase##TEST_CASE_NAME(TestCase *tcase)			\
	{                                                                    \
		assert(tcase != NULL && "Can't be null tcase tests");        \
		TestCaseFrame tframe;                                        \
		tframe.state   = stackjmp(&tframe.buf);                      \
		tframe.counter = 0;                                          \
		do

#define Test(TEST_NAME)                         \
	tframe.current_test = #TEST_NAME;       \
	/* Count all the tests */               \
	if (tframe.state == 0) tcase->amount++; \
	if (tframe.state == ++tframe.counter)

#define EndTestCase                                                                     \
	while (0)                                                                       \
		;                                                                       \
	assert(tcase->amount > 0 && "The testcase should have atleast one test"); \
	if (tframe.state > 0 && tframe.state <= (int) tcase->amount)	\
		putchar('.');						\
	if (tframe.state < (int) tcase->amount) {			\
		jmpback(&tframe.buf, tframe.state + 1);			\
	}								\
	}

/* head_tc: A pointer to the last linked test case. */
extern TC *head_tc;

/* link_tcases: Links test case structures together for the testing process. */
extern void link_tcase(TC *tcase);

#undef F
#undef TC
#undef TF
#endif
