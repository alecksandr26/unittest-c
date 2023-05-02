/*!
  @file unittest.h
  @brief A set of macros to create new testcases or thats the idea.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef __UNIT_TEST_H__
#define __UNIT_TEST_H__

#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <except.h>

#define T TestCaseFrame

/* The structure to keep track */
typedef struct T T;
struct T {
	volatile int test_to_execute;
	const char *file, *name, *current_test;
	size_t amount;
	int line, counter;
	JmpBuf buf;
};

/* To create a new testcase */
#define TestCase(TEST_CASE_NAME)					\
	void TEST_CASE_NAME() {						\
	TestCaseFrame test_case;					\
	test_case.name = #TEST_CASE_NAME;				\
	test_case.amount = 0;						\
	test_case.test_to_execute = stackjmp(&test_case.buf);		\
	test_case.counter = 0;						\
	do 

#define Test(TEST_NAME)							\
	test_case.current_test = #TEST_NAME;				\
	/* Count all the tests */					\
	if (test_case.test_to_execute == 0)				\
		test_case.amount++;					\
	if (test_case.test_to_execute == test_case.counter++)

#define EndTestCase while (0);						\
	if (test_case.test_to_execute < (int) test_case.amount - 1)	\
		jmpback(&test_case.buf, test_case.test_to_execute + 1);	\
	}



#undef T
#endif
