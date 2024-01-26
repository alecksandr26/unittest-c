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
#include <sys/time.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

bool unittest_running_tests = false;
int unittest_ret = 0;

/* unittest_print_results: Prints the results of the executed testcases. */
static void unittest_print_tests_results(double duration, size_t crashed_testcases, size_t failed_testcases,
					 size_t failed_tests, size_t warned_tests, size_t count_tests)
{	
	LOG("\n");

	for (size_t i = 0; i < crashed_testcases; i++)
		unittest_print_crashed_testcase(unittest_info_crashed_testcases[i]);

	for (size_t i = 0; i < failed_testcases; i++)
		unittest_print_faild_testcase(infofails[i]);

	
	LOG(DIV_LINE_STR);
	LOG("Ran %zu test in %fs\n", count_tests, duration);

	if (failed_tests == 0 && crashed_testcases == 0 && warned_tests == 0 && failed_testcases) {
		LOG("\nOk \n\n");
		unittest_ret = 0;
	}

	if (crashed_testcases) {
		LOG("\nCRASHED(crashes=%zu)\n", crashed_testcases);
		unittest_ret = -1;
	}

	if (failed_tests) {
		LOG("\nFAILED(failures=%zu)\n\n", failed_tests);
		unittest_ret = -1;
	}

	if (warned_tests) {
		LOG("\nWARNED(warnings=%zu)\n\n", warned_tests);
		unittest_ret = 1;
	}
}

/* unittest_run_tests: Takes the linked list of testcases and run isolated it each individual it. */
void unittest_run_tests(void)
{
	assert(unittest_head_tc != NULL && "Should be at least one test");
	size_t count_tests, successed_tests, failed_tests, warned_tests,
		crashed_testcases, failed_testcases;
	
	/* Execute each testcase */
	failed_testcases = crashed_testcases = count_tests = successed_tests = failed_tests = warned_tests = 0;
	/* clock_t start_time				       = clock(); */
	struct timeval start_time, end_time;
	gettimeofday(&start_time, NULL);

	while (unittest_head_tc != NULL) {
		unittest_run_isolated_testcase(unittest_head_tc);
		
		if (unittest_head_tc->sigstatus == 0
		    && unittest_head_tc->retstatus == EXIT_SUCCESS) {
			
			successed_tests += unittest_head_tc->amount
				- unittest_head_tc->failed_info.number_failed_asserts
				- unittest_head_tc->failed_info.number_warning_expects;
			
			/* Catch its failed asserts info */
			if (unittest_head_tc->failed_info.number_failed_asserts
			    || unittest_head_tc->failed_info.number_warning_expects)
				infofails[failed_testcases++] = &unittest_head_tc->failed_info;
			
			failed_tests += unittest_head_tc->failed_info.number_failed_asserts;
			warned_tests += unittest_head_tc->failed_info.number_warning_expects;
		} else {
			LOG("E"); /* Print for a crash  */
			unittest_info_crashed_testcases[crashed_testcases] = &unittest_head_tc->crashed_info;
			unittest_catch_info_crashed(unittest_info_crashed_testcases[crashed_testcases],
						    unittest_head_tc);
		}

		count_tests += unittest_head_tc->amount;

		/* Move to the next test */
		unittest_head_tc = unittest_head_tc->next;
	}
	
	/* clock_t end_time = clock(); */
	/* double duration = (end_time - start_time) / CLOCKS_PER_SEC; */
	gettimeofday(&end_time, NULL);
	double duration = (end_time.tv_sec - start_time.tv_sec) +
		(end_time.tv_usec - start_time.tv_usec) / 1000000.0;
	
	/* Printing section */
	unittest_print_tests_results(duration, crashed_testcases, failed_testcases, failed_tests,
				     warned_tests, count_tests);
}
