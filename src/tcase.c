/*!
  @file tcase.c
  @brief Defines a pointer to the head of the test cases list, provides a function to link a new
  test case to the list, and defines macros to handle the test cases and test functions.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_tcase.h"


#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#include <trycatch.h>
#include <assert.h>
#include <string.h>

/* unittest_head_tc: A pointer to the last linked test case. */
UnitTestCase    *unittest_head_tc	 = NULL;
Except UnittestNoneTests = {"The testcase should have at least one test"};

/* unittest_run_isolated_testcase:  Executes a test case in isolation, capturing the signal status
   and, in case of a crash, the return status. */
void unittest_run_isolated_testcase(UnitTestCase *tc)
{
	assert(tc != NULL && "Shouldn't be null");
	
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
		tc->testcase(tc);

		// Write the data to the pipe
		write(pipefd[1], tc, sizeof(*tc));

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
				read(pipefd[0], tc, sizeof(*tc));

				/* Close the read pipe */
				close(pipefd[0]);
				tc->retstatus = EXIT_SUCCESS;
				tc->sigstatus = 0;
				return;
			}
			
			tc->retstatus = WEXITSTATUS(status);
			tc->sigstatus = 0;
			return;
		} else {
			/* The program was aborted */
			close(pipefd[0]);
			tc->sigstatus = WTERMSIG(status);
			return;
		}
	}

	assert(0 && "Shoulnd't be executed this part of the code");
}


/* unittest_catch_info_crashed: Catch the information from a crashed testcase. */
void unittest_catch_info_crashed(UnitTestCaseErrorInfo *info, UnitTestCase *tc)
{
	info->file = tc->file;
	info->unitcase = tc->name;
	info->line = tc->line;
	
	if (tc->sigstatus == 0) /* Uknow encountered error */
		sprintf(info->msg, "Encountered an error, exited with status %i",
			tc->retstatus);
	else
		strcpy(info->msg, unittest_signal_error_str(tc->sigstatus));
}

/* link_tcases: Links test case structures together and then be executed. */
void unittest_link_tcase(UnitTestCase *tc)
{
	tc->next	 = unittest_head_tc;
	unittest_head_tc = tc;
}

/* unittest_catch_info_faild: Catch the information from a test failed. */
void unittest_catch_info_faild(UnitTestInfoFailed *info, UnitTestCase *tc)
{
	info->unitcase = tc->name;
	info->file = tc->file;
}


