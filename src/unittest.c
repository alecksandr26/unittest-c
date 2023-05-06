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

void unittest_check_testdir_exist(const char *test_dir)
{
	DIR *dir;
	if ((dir = opendir(test_dir)) == NULL) {
		closedir(dir);
		throw_except(UnittestErrorTestBaseDoesntExist);
	}

	closedir(dir);
}

void unittest_run_tests(void)
{
	assert(unittest_head_tc != NULL && "Should be at least one test");
	size_t		    count_tests, success_test, failed_test;
	UnitTestInfoFailed *infofails[MAX_AMOUNT_OF_TESTS_IN_TESTCASES];

	/* Execute each testcase */
	count_tests = success_test = failed_test = 0;
	clock_t start_time			 = clock();
	while (unittest_head_tc != NULL) {
		/* Run the testscase */
		unittest_head_tc->test(unittest_head_tc);
		count_tests += unittest_head_tc->amount;
		success_test +=
			unittest_head_tc->amount - unittest_head_tc->amount_failed;

		/* Catch its failes info */
		for (size_t i = 0; i < unittest_head_tc->amount_failed; i++) {
			infofails[failed_test] = &unittest_head_tc->failed_info[i];
			infofails[failed_test]->unitcase = unittest_head_tc->name;
			infofails[failed_test++]->file	 = unittest_head_tc->file;
		}

		/* Move to the next test */
		unittest_head_tc = unittest_head_tc->next;
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
