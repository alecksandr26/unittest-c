/*!
  @file unittest.c
  @brief

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_exceptions.h"
#include "../include/unittest_tcase.h"

#include <assert.h>
#include <dirent.h>
#include <except.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void check_testdir_exist(const char *test_dir)
{
	DIR *dir;
	if ((dir = opendir(test_dir)) == NULL) {
		closedir(dir);
		throw_except(UnittestErrorTestBaseDoesntExist);
	}

	closedir(dir);
}

void run_tests(void)
{
	assert(head_tc != NULL && "Should be at least one test");
	size_t		count_tests, success_test, failed_test;
	TestInfoFailed *infofails[MAX_AMOUNT_OF_TESTS_IN_TESTCASES];

	/* Execute each testcase */
	count_tests = success_test = failed_test = 0;
	clock_t start_time			 = clock();
	while (head_tc != NULL) {
		/* Run the testscase */
		head_tc->test(head_tc);
		count_tests += head_tc->amount;
		success_test += head_tc->amount - head_tc->amount_failed;

		/* Catch its failes info */
		for (size_t i = 0; i < head_tc->amount_failed; i++) {
			infofails[failed_test]	       = &head_tc->failed_info[i];
			infofails[failed_test]->tcase  = head_tc->name;
			infofails[failed_test++]->file = head_tc->file;
		}

		/* Move to the next test */
		head_tc = head_tc->next;
	}
	clock_t end_time = clock();
	printf("\n");

	for (size_t i = 0; i < failed_test; i++)
		unittest_print_faild_test(infofails[i]);

	puts("---------------------------------------------------------------------------"
	     "-----------");
	if (failed_test == 0) {
		printf("Ran %zu test in %fs\n", count_tests,
		       (double) (end_time - start_time) / CLOCKS_PER_SEC);
		printf("\nOk \n\n");
	} else {
		printf("Ran %zu test in %fs\n", count_tests,
		       (double) (end_time - start_time) / CLOCKS_PER_SEC);
		printf("\nFAILED(failures=%zu)\n\n", failed_test);
	}
}
