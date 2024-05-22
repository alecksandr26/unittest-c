/*!
  @file unittest_tcase.h
  @brief defines the structures and functions necessary for creating and running test cases in for this
  unit testing framework. It includes structures to keep track of test cases and their individual tests,
  as well as macros for defining test cases, individual tests, and ending test cases.
  The file also defines a function for linking together multiple test cases.

  @author Erick Carrillo.
  @copyright Copyright (C) 2023, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_TESTCASE_INCLUDED
#define UNITTEST_TESTCASE_INCLUDED

#include "unittest_debug.h"
#include "unittest_def.h"
#include "unittest_info.h"

#include <stddef.h>
#include <trycatch.h>

/* The UnitTestCase struct represents a test case and includes information such as file
   name, test
   name, test function, and an array of failed test info. */
typedef struct UnitTestCase UnitTestCase;
struct UnitTestCase {
	const char   *file, *name;
	char	      res;
	size_t	      amount;
	UnitTestCase *next;
	int	      line, retstatus, sigstatus;

	/* Catch the test function */
	void (*testcase)(UnitTestCase *);
	UnitTestInfo    info;
	UnitTestCaseErrorInfo crashed_info;
};

/* The UnitTestCaseFrame structure is a data structure that contains information about the
 * state of a test case. */
typedef struct {
	volatile int state;
	const char  *current_test;
	int	     counter;
	JmpBuf	     buf;
} UnitTestCaseFrame;

/* These are macros used to define and run test cases. */
#define TESTCASE(TEST_CASE_NAME)                                           \
	void	     TESTCASE_##TEST_CASE_NAME(UnitTestCase *unitcase);    \
	UnitTestCase TEST_CASE_NAME = {                                    \
		.file	  = __FILE__,                                      \
		.name	  = #TEST_CASE_NAME,                               \
		.amount	  = 0,                                             \
		.next	  = NULL,                                          \
		.testcase = &(TESTCASE_##TEST_CASE_NAME),                  \
		.line	  = __LINE__,                                      \
		.info =                                             \
			{                                                  \
				      .unitcase		= #TEST_CASE_NAME, \
				      .file			= __FILE__,        \
				      .number_failed_asserts	= 0,               \
				      .number_warning_expects = 0,               \
				      },                                                 \
	};                                                                 \
	void TESTCASE_##TEST_CASE_NAME(UnitTestCase *unitcase)             \
	{                                                                  \
		UnitTestCaseFrame unitframe;                               \
		unitframe.state = stackjmp(&unitframe.buf);                \
		if (unitframe.state > 1) LOG("%c", unitcase->res);         \
		if ((size_t) unitframe.state > unitcase->amount) return; \
		unitframe.counter = 0;                                     \
		do

#define TEST(TEST_NAME)                               \
	unitframe.current_test = #TEST_NAME;          \
	/* Count all the tests */                     \
	if (unitframe.state == 0) unitcase->amount++; \
	if (unitframe.state == ++unitframe.counter && (unitcase->res = '.'))

#define ENDTESTCASE                                                \
	while (0)                                                  \
		;                                                  \
	if (unitcase->amount == 0 ||                               \
	    unitcase->amount > MAX_AMOUNT_OF_TESTS_IN_TESTCASES)   \
		ABORT("Error invalid amount of test in testcase"); \
	if (unitframe.state <= (int) unitcase->amount)             \
		jmpback(&unitframe.buf, unitframe.state + 1);      \
	}

/* unittest_head_tc: A pointer to the last linked test case. */
extern UnitTestCase *unittest_head_tc;
extern int	     unittest_mute_mode;

/* link_tcases: Links test case structures together and then be executed. */
extern void unittest_link_tcase(UnitTestCase *tc);

/* unittest_run_isolated_testcase:  Executes a test case in isolation, capturing the
   signal status
   and, in case of a crash, the return status. */
extern void unittest_run_isolated_testcase(UnitTestCase *tcase);

/* unittest_catch_info_crashed: Catch the information from a crashed testcase. */
extern void unittest_catch_info_crashed(UnitTestCaseErrorInfo *info, UnitTestCase *tcase);

#endif
