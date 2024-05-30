/*!
  @file tcase.c
  @brief Defines a pointer to the head of the test cases list, provides a function to link a new
  test case to the list, and defines macros to handle the test cases and test functions.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_def.h"
#include "../include/unittest_tcase.h"

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* unittest_head_tc: A pointer to the last linked test case. */
UnitTestCase *unittest_head_tc = NULL;

/* unittest_run_isolated_testcase:  Executes a test case in isolation, capturing the
   signal status
   and, in case of a crash, the return status. */
void unittest_run_isolated_testcase(UnitTestCase *tc)
{
	assert(tc != NULL && "Shouldn't be null");

	pid_t child_pid;
	int   status;
	int   shmid; /* The shared memory */

	if ((shmid = shmget(IPC_PRIVATE, sizeof(UnitTestCase), IPC_CREAT | 0666)) < 0)
		ABORT("Error creating shared memory for unittest case: errno: %s\n",
		      strerror(errno));

	/* create the child process */
	child_pid = fork();

	if (child_pid == -1)
		ABORT("Error forking the process for executing isolated the testcase: "
		      "errno: %s\n",
		      strerror(errno));

	if (child_pid == 0) { /* Child process */

		/* Get a pointer to the shared memory */
		UnitTestCase *shared_tc = (UnitTestCase *) shmat(shmid, NULL, 0);
		memcpy(shared_tc, tc, sizeof(UnitTestCase));

		/* Execute the testcase */
		shared_tc->testcase(shared_tc);

		shmdt(shared_tc);

		exit(EXIT_SUCCESS);
	} else {
		/* Father process */

		/* Wait for the execution of the testcase */
		wait(&status);

		if (WIFEXITED(status)) {
			if (WEXITSTATUS(status) == EXIT_SUCCESS) {
				UnitTestCase *shared_tc =
					(UnitTestCase *) shmat(shmid, NULL, 0);

				memcpy(tc, shared_tc, sizeof(UnitTestCase));

				tc->retstatus = EXIT_SUCCESS;
				tc->sigstatus = 0;

				shmdt(shared_tc);
				shmctl(shmid, IPC_RMID,
				       NULL);	     // Cleanup shared memory

				return;
			}

			tc->retstatus = WEXITSTATUS(status);
			tc->sigstatus = 0;
			shmctl(shmid, IPC_RMID, NULL);	      // Cleanup shared memory
			return;
		} else {
			/* The program was aborted */
			tc->sigstatus = WTERMSIG(status);
			shmctl(shmid, IPC_RMID, NULL);	      // Cleanup shared memory
			return;
		}
	}

	assert(0 && "Shoulnd't be executed this part of the code");
}

/* unittest_catch_info_crashed: Catch the information from a crashed testcase. */
void unittest_catch_info_crashed(UnitTestCaseErrorInfo *info, UnitTestCase *tc)
{
	info->file     = tc->file;
	info->unitcase = tc->name;
	info->line     = tc->line;

	if (tc->sigstatus == 0) /* Uknow encountered error */
		sprintf(info->msg, "Encountered an error, exited with status %i",
			tc->retstatus);
	else strcpy(info->msg, unittest_signal_error_str(tc->sigstatus));
}

/* link_tcases: Links test case structures together and then be executed. */
void unittest_link_tcase(UnitTestCase *tc)
{
	assert(tc != NULL && "Can't be null");

	tc->next	 = unittest_head_tc;
	unittest_head_tc = tc;
}

/* unittest_catch_info_faild: Catch the information from a test failed. */
void unittest_catch_info_faild(UnitTestInfo *info, UnitTestCase *tc)
{
	assert(info != NULL && tc != NULL && "Can't be null");

	info->unitcase = tc->name;
	info->file     = tc->file;
}
