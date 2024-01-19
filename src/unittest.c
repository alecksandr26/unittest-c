/*!
  @file unittest.c
  @brief A few general implementations for the project.

  @author Erick Carrillo.
  @copyright Copyright (C) 2023, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_def.h"
#include "../include/unittest_debug.h"
#include "../include/unittest_tcase.h"

#include <assert.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>

int unittest_ret = 0;

/* unittest_print_results: Prints the results of the executed testcases. */
static void unittest_print_tests_results(double duration, size_t crashed_tests, size_t failed_tests,
					 size_t count_tests)
{
	LOG("\n");

	for (size_t i = 0; i < crashed_tests; i++)
		unittest_print_crashed_testcase(unittest_info_crashed_testcases[i]);

	for (size_t i = 0; i < failed_tests; i++)
		unittest_print_faild_test(infofails[i]);

	LOG("---------------------------------------------------------------------------"
	    "-----------\n");
	LOG("Ran %zu test in %fs\n", count_tests, duration);

	if (failed_tests == 0 && crashed_tests == 0) {
		LOG("\nOk \n\n");
		unittest_ret = 0;
	}

	if (crashed_tests) {
		LOG("\nCRASHED(crashes=%zu)\n", crashed_tests);
		unittest_ret = -1;
	}

	if (failed_tests) {
		LOG("\nFAILED(failures=%zu)\n\n", failed_tests);
		unittest_ret = -1;
	}
}

/* unittest_run_tests: Takes the linked list of testcases and run isolated it each individual it. */
void unittest_run_tests(void)
{
	assert(unittest_head_tc != NULL && "Should be at least one test");
	size_t		    count_tests, success_test, failed_tests, crashed_tests;

	/* Execute each testcase */
	crashed_tests = count_tests = success_test = failed_tests = 0;
	clock_t start_time				       = clock();
	while (unittest_head_tc != NULL) {
		unittest_run_isolated_testcase(unittest_head_tc);
		
		if (unittest_head_tc->sigstatus == 0
		    && unittest_head_tc->retstatus == EXIT_SUCCESS) {
			
			success_test += unittest_head_tc->amount -
				unittest_head_tc->amount_failed;

			/* Catch its failes info */
			for (size_t i = 0; i < unittest_head_tc->amount_failed;
			     i++) {
				infofails[failed_tests] =
					&unittest_head_tc->failed_info[i];
				unittest_catch_info_faild(infofails[failed_tests++], unittest_head_tc);
			}
		} else {
			LOG("E"); /* Print for a crash  */
			unittest_info_crashed_testcases[crashed_tests] = &unittest_head_tc->crashed_info;
			unittest_catch_info_crashed(unittest_info_crashed_testcases[crashed_tests],
						    unittest_head_tc);
		}

		count_tests += unittest_head_tc->amount;

		/* Move to the next test */
		unittest_head_tc = unittest_head_tc->next;
	}
	clock_t end_time = clock();
	double duration = end_time - start_time / CLOCKS_PER_SEC;

	/* Printing section */
	unittest_print_tests_results(duration, crashed_tests, failed_tests, count_tests);
}
