/*!
  @file unittest.c
  @brief A set of macros to create new testcases or thats the idea.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/


#include <stddef.h>
#include <stddef.h>
#include <stdarg.h>
#include <except.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "../include/unittest.h"
#define T TestCaseFrame
#define S Suit

/* To keep track from all the created tests */
S *head = NULL;

void run_tests(void)
{
	assert(head != NULL && "Should be at least one suit for testing");
	size_t amount_tests = 0;
	
	/* Execute each testcase */
	clock_t start_time = clock();
	while (head != NULL) {
		assert(head->amount > 0 && "For each suit at least should have one testcase");
		amount_tests += head->amount;
		for (size_t i = 0; i < head->amount; i++) {
			putchar('.');
			head->cases[i]();
		}
		
		/* Move to the next suit */
		head = head->next;
	}

	clock_t end_time = clock();
	printf("\n");
	puts("----------------------------------------------------------------------");
	printf("Ran %zu test in %fs\n", amount_tests, (double)(end_time - start_time) / CLOCKS_PER_SEC);

	printf("\nOk\n");
	
}


#undef S
#undef T
