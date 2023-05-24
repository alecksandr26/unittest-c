/*!
  @file unittest.c
  @brief A few general implementations for the project.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_exceptions.h"
#include "../include/unittest_tcase.h"

#include <assert.h>
#include <except.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

extern uint8_t unittest_run_valgrind;
uint8_t	       unittest_running_tests = 0;

/* All the paths to files */
int unittest_fetched_files_name = 0, unittest_mute_mode = 0, unittest_ret = 0,
    unittest_fd_stdout = 1;
char unittest_basedir[100], unittest_file[100], unittest_outfile[100],
	unittest_testdir[100], unittest_objdir[100], unittest_hashed_file[100],
	unittest_extra_flags[200];

#ifndef NDEBUG
uint8_t is_root_folder = 0;
#endif

/* get_basedir: Gets the base dir from path to a file */
static void get_basedir(const char *file, char *basedir)
{
	int n = strlen(file);

	/* Iterates until finds a '/' */
	for (; n >= 0 && file[n] != '/'; n--)
		;

	if (n > 0) memcpy(basedir, file, n + 1);
}

/* executing_from_basedir: To know if im executing the program in the basedir */
static uint8_t executing_from_basedir(const char *file)
{
	/* Get the current working directory */
	char cwd[1024], basedir[255], fdir[255]; /* First dir */
	int  n, m;

	memset(cwd, 0, sizeof(cwd));
	memset(basedir, 0, sizeof(basedir));

	get_basedir(file, basedir);
	getcwd(cwd, sizeof(cwd));

	/* Count the amount of slashes in basedir */
	m = 0;
	for (size_t i = 0; i < strlen(basedir); i++)
		if (basedir[i] == '/') m++;

	for (n = strlen(cwd); n >= 0; n--) {
		if (cwd[n] == '/') m--;

		if (m == 0) break;
	}

	memset(fdir, 0, sizeof(fdir));
	memcpy(fdir, cwd + n + 1, strlen(cwd) - n);
	fdir[strlen(fdir)] = '/';

	if (strcmp(fdir, basedir) == 0) return 1;
#ifndef NDEBUG
	else is_root_folder = 1;
#endif

	/* we are in another directory */
	return 0;
}

/* unittest_fetch_filesname: This functions gets the paths for the needed files */
void unittest_fetch_filesname(const char *file, const char *outfile, const char *testdir,
			      const char *objdir, const char *hashed_file)
{
	if (unittest_fetched_files_name) return;

	memset(unittest_file, 0, sizeof(unittest_file));
	memset(unittest_basedir, 0, sizeof(unittest_basedir));
	memset(unittest_outfile, 0, sizeof(unittest_outfile));

	/* Patch all the filesname */
	if (executing_from_basedir(file)) { /* Try to find that we are in the basedir */
		int i;

		/* Try to find where it is '/' */
		for (i = strlen(file); i >= 0 && file[i] != '/'; i--)
			;
		strcpy(unittest_file, file + i + 1);
	} else {
		get_basedir(file, unittest_basedir); /* get the basedir */
		strcpy(unittest_file, file);
	}

	/* Dump the basedir and fill all the variabels */
	strcpy(unittest_outfile, unittest_basedir);
	strcat(unittest_outfile, outfile);

	strcpy(unittest_testdir, unittest_basedir);
	strcat(unittest_testdir, testdir);

	strcpy(unittest_objdir, unittest_testdir);
	strcat(unittest_objdir, objdir);

	strcpy(unittest_hashed_file, unittest_testdir);
	strcat(unittest_hashed_file, hashed_file);

	unittest_fetched_files_name = 1;
}

void unittest_check_testdir_exist(void)
{
	if (access(unittest_testdir, F_OK) != 0)
		throw_except(UnittestErrorTestBaseDoesntExist);
}

/* unittest_attach_extra_flags: To attach new flags to the  */
void unittest_attach_extra_flags(const char *flags)
{
	memset(unittest_extra_flags, 0, sizeof(unittest_extra_flags));
	strcpy(unittest_extra_flags, unittest_basedir);
	strcat(unittest_extra_flags, flags);
}

/* unittest_run_tests: Return 0 if there weren't any failed test otherwise return 1 */
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
		unittest_head_tc->testcase(unittest_head_tc);
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
	LOG("\n");

	for (size_t i = 0; i < failed_test; i++)
		unittest_print_faild_test(infofails[i]);

	LOG("---------------------------------------------------------------------------"
	    "-----------\n");
	LOG("Ran %zu test in %fs\n", count_tests,
	    (double) (end_time - start_time) / CLOCKS_PER_SEC);

	if (failed_test == 0) {
		LOG("\nOk \n\n");
		unittest_ret = 0;
	} else {
		LOG("\nFAILED(failures=%zu)\n\n", failed_test);
		unittest_ret = -1;
	}

	/* Close the file */

	if (unittest_mute_mode) close(unittest_fd_stdout); /* Close /dev/null */
}
