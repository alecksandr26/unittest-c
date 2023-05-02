/*!
  @file unittest.h
  @brief A set of macros to create new testcases or thats the idea.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef __UNIT_TEST_H__
#define __UNIT_TEST_H__

#include <stddef.h>
#include <string.h>
#include <except.h>

#define T TestCaseFrame
#define S Suit
#define MAX_AMOUNT_OF_TESTS_IN_SUITS 1024

/* The structure to keep track */
typedef struct T T;
struct T {
	volatile int test_to_execute;
	const char *file, *name, *current_test;
	size_t amount;
	int line, counter;
	JmpBuf buf;
};

typedef void (*test_case_ptr)(void);
/* To create a suit of test cases */
typedef struct S S;
struct S {
	test_case_ptr cases[MAX_AMOUNT_OF_TESTS_IN_SUITS];
	size_t amount;
	const char *name;
	struct S *next;	/* For linking suits */
};

/* To run the whole tests */
extern void run_tests(void);
extern S *head;

/* To create a new testcase */
#define TestCase(TEST_CASE_NAME)					\
	static void TEST_CASE_NAME(void) {				\
	TestCaseFrame test_case;					\
	test_case.name = #TEST_CASE_NAME;				\
	test_case.amount = 0;						\
	test_case.test_to_execute = stackjmp(&test_case.buf);		\
	test_case.counter = 0;						\
	do 

/* To run an specific test */
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

/* To create a new suit */
#define NEW_SUIT(SUIT_NAME, ...)					\
	Suit SUIT_NAME = {{__VA_ARGS__},				\
			  sizeof((test_case_ptr[]) {__VA_ARGS__}) / sizeof(test_case_ptr), \
			  #SUIT_NAME,					\
			  NULL						\
	}								

/* CATCH_SUIT: To append the testcases from a suit */
#define CATCH_SUIT(SUIT_NAME)			\
	SUIT_NAME.next = head;			\
	head = &SUIT_NAME

/* To run the suit */
#define RUN() run_tests()

#undef T
#undef S
#endif
