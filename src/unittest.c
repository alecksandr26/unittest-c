/*!
  @file unittest.c
  @brief A few general implementations for the project.

  @author Erick Carrillo.
  @copyright Copyright (C) 2023, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_exceptions.h"
#include "../include/unittest_tcase.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <trycatch.h>
#include <unistd.h>

extern uint8_t unittest_run_valgrind;
uint8_t	       unittest_running_tests = 0;

/* All the paths to files */
int unittest_fetched_files_name = 0, unittest_mute_mode = 0, unittest_ret = 0,
    unittest_fd_stdout = 1;
char unittest_basedir[100], unittest_file[100], unittest_outfile[100],
	unittest_testdir[100], unittest_objdir[100], unittest_hashed_file[100],
	unittest_extra_linking_flags[200], unittest_extra_compile_flags[200];

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
	if (access(unittest_testdir, F_OK) != 0) throw(UnittestErrorTestBaseDoesntExist);
}

/* unittest_attach_extra_linking_flags: To attach more flags to the linking compilation */
void unittest_attach_extra_linking_flags(const char *flags)
{
	assert(flags != NULL);
	memset(unittest_extra_linking_flags, 0, sizeof(unittest_extra_linking_flags));
	strcpy(unittest_extra_linking_flags, unittest_basedir);
	strcat(unittest_extra_linking_flags, flags);
}

void unittest_attach_extra_compile_flags(const char *flags)
{
	assert(flags != NULL);
	memset(unittest_extra_compile_flags, 0, sizeof(unittest_extra_compile_flags));
	strcpy(unittest_extra_compile_flags, unittest_basedir);
	strcat(unittest_extra_compile_flags, flags);
}

/* running_isolated_testcase: To execut an isolated testcase */
void running_isolated_testcase(UnitTestCase *tcase, int *sigstatus, int *retstatus)
{
	pid_t child_pid;
	int   pipefd[2];	// File descriptors for the pipe
	int   status;

	if (pipe(pipefd) == -1) {
		LOG("IMPOSSIBLE TO BUILT THE PIPES\n");
		exit(EXIT_FAILURE);
	}

	/* create the child process */
	child_pid = fork();

	if (child_pid == -1) {
		LOG("IMPOSSIBLE TO FORK\n");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0) {
		/* Child process */

		// Close the read end of the pipes
		close(pipefd[0]);

		/* Execute the testcase */
		tcase->testcase(tcase);

		// Write the data to the pipe
		write(pipefd[1], tcase, sizeof(*tcase));

		// Close the write end of the pipe
		close(pipefd[1]);

		/* Terminated the program with success */
		exit(EXIT_SUCCESS);
	} else {
		/* Father process */

		// Close the write end of the pipes
		close(pipefd[1]);

		/* Wait for the execution of the testcase */
		wait(&status);

		if (WIFEXITED(status)) {
			if (WEXITSTATUS(status) == EXIT_SUCCESS) {
				read(pipefd[0], tcase, sizeof(*tcase));

				/* Close the read pipe */
				close(pipefd[0]);
				*retstatus = EXIT_SUCCESS;
				*sigstatus = 0;
				return;
			}

			*retstatus = WEXITSTATUS(status);
			*sigstatus = 0;
			return;
		} else {
			/* The program was aborted */
			close(pipefd[0]);
			*sigstatus = WTERMSIG(status);
			return;
		}
	}

	assert(0 && "Shoulnd't be executed this part of the code");
}

/* Sime implemention of an assert */
void unittest_print_crashed_testcase(UnitTestCaseErrorInfo *info)
{
	LOG("==========================================================================="
	    "===========\n");

	LOG("ERROR:\t\t(%s)\n", info->unitcase);
	LOG("---------------------------------------------------------------------------"
	    "-----------\n");
	LOG("Traceback...\n");
	LOG("\tFile \"%s\", line %i, in %s\n", info->file, info->line, info->unitcase);
	LOG("ErrorDescription:\t \"%s\"\n\n", info->sigmsg);
}

const char *signal_error_msg(int signum)
{
	switch (signum) {
	case SIGSEGV: return "Segmentation fault (SIGSEGV): Invalid memory access";
	case SIGABRT: return "Aborted (SIGABRT): Program has been explicitly aborted";
	case SIGILL: return "Illegal Instruction (SIGILL): Invalid machine instruction";
	case SIGFPE:
		return "Floating-Point Exception (SIGFPE): Illegal floating-point "
		       "operation";
	case SIGBUS: return "Bus Error (SIGBUS): Invalid memory access or misalignment";
	case SIGTRAP: return "Trace Trap (SIGTRAP): Debugging event";
	case SIGSYS: return "Bad System Call (SIGSYS): Invalid system call";
	case SIGPIPE: return "Broken Pipe (SIGPIPE): Write to a closed pipe/socket";
	case SIGXCPU:
		return "Cputime Limit Exceeded (SIGXCPU): Process exceeded CPU time "
		       "limit";
	case SIGXFSZ:
		return "File Size Limit Exceeded (SIGXFSZ): Process exceeded file size "
		       "limit";
	default: return "Unknown Signal";
	}
}

/* unittest_run_tests: Return 0 if there weren't any failed test otherwise return 1 */
void unittest_run_tests(void)
{
	assert(unittest_head_tc != NULL && "Should be at least one test");
	size_t		    count_test, success_test, failed_test, crashed_test;
	UnitTestInfoFailed *infofails[MAX_AMOUNT_OF_TESTS_IN_TESTCASES];

	/* Execute each testcase */
	crashed_test = count_test = success_test = failed_test = 0;
	clock_t start_time				       = clock();
	while (unittest_head_tc != NULL) {
		/* Run the testscase */
		int retstatus, sigstatus;
		running_isolated_testcase(unittest_head_tc, &sigstatus, &retstatus);

		if (sigstatus == 0) {
			if (retstatus == EXIT_SUCCESS) {
				success_test += unittest_head_tc->amount -
						unittest_head_tc->amount_failed;

				/* Catch its failes info */
				for (size_t i = 0; i < unittest_head_tc->amount_failed;
				     i++) {
					infofails[failed_test] =
						&unittest_head_tc->failed_info[i];
					infofails[failed_test]->unitcase =
						unittest_head_tc->name;
					infofails[failed_test++]->file =
						unittest_head_tc->file;
				}
			} else {
				LOG("E"); /* Print for a crash  */
				unittest_info_crashed_testcases[crashed_test].file =
					(char *) unittest_head_tc->file;
				unittest_info_crashed_testcases[crashed_test].unitcase =
					(char *) unittest_head_tc->name;
				sprintf(unittest_info_crashed_testcases[crashed_test]
						.sigmsg,
					"Encountered an error, exited with status %i",
					retstatus);
				unittest_info_crashed_testcases[crashed_test++].line =
					unittest_head_tc->line;
			}
		} else {
			LOG("E"); /* Print for a crash  */
			unittest_info_crashed_testcases[crashed_test].file =
				(char *) unittest_head_tc->file;
			unittest_info_crashed_testcases[crashed_test].unitcase =
				(char *) unittest_head_tc->name;
			strcpy(unittest_info_crashed_testcases[crashed_test].sigmsg,
			       signal_error_msg(sigstatus));
			unittest_info_crashed_testcases[crashed_test++].line =
				unittest_head_tc->line;
		}

		count_test += unittest_head_tc->amount;

		/* Move to the next test */
		unittest_head_tc = unittest_head_tc->next;
	}
	clock_t end_time = clock();
	LOG("\n");

	for (size_t i = 0; i < crashed_test; i++)
		unittest_print_crashed_testcase(&unittest_info_crashed_testcases[i]);

	for (size_t i = 0; i < failed_test; i++)
		unittest_print_faild_test(infofails[i]);

	LOG("---------------------------------------------------------------------------"
	    "-----------\n");
	LOG("Ran %zu test in %fs\n", count_test,
	    (double) (end_time - start_time) / CLOCKS_PER_SEC);

	if (failed_test == 0 && crashed_test == 0) {
		LOG("\nOk \n\n");
		unittest_ret = 0;
	}

	if (crashed_test) {
		LOG("\nCRASHED(crashes=%zu)\n", crashed_test);
		unittest_ret = -1;
	}

	if (failed_test) {
		LOG("\nFAILED(failures=%zu)\n\n", failed_test);
		unittest_ret = -1;
	}

	/* Close the file */

	if (unittest_mute_mode) close(unittest_fd_stdout); /* Close /dev/null */
}
