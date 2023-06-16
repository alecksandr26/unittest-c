/*!
  @file unittest_recompile.c
  @brief This module contains implementations for recompiling the main executable
  program with or without test files and for rerunning the program after recompilation.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <tc.h>
#include <unistd.h>
#include <wait.h>

#include "../include/unittest_debug.h"
#include "../include/unittest_recompile.h"

#define C UnitCompilerContex

#include "../include/unittest_tfile.h"
#define F UnitTestFile

#include "../include/unittest_map.h"

#ifndef NDEBUG
#undef LIB_UNITTEST
#define LIB_UNITTEST "../lib/libunittest.a"
#endif

/* Variables to have all the paths to file */
extern const char unittest_basedir[100], unittest_file[100], unittest_outfile[100],
	unittest_testdir[100], unittest_objdir[100], unittest_hashed_file[100],
	unittest_extra_flags[200];

extern int unittest_mute_mode;
uint8_t	   unittest_run_valgrind    = 0; /* By default it is not going to run valgrind  */
Except	   UnittestErrorCreatingDir = {
	    "Error creating the object dir \"OBJ_DIR\" at \"TEST_DIR\""};

char *args[50];	      /* Max 50 arguments */
char  args_buf[1024]; /* Buffer where the args will be allocated */

static void create_obj_directory(void)
{
	/* First check if the directoy exist */
	if (access(unittest_objdir, F_OK) == 0) return; /* Already exist */

	if (mkdir(unittest_objdir, 0775) != 0) throw(UnittestErrorCreatingDir);
}

/* compile: Compiles something running a child process and returns it status */
static int compile(const C c, const char *args[50])
{
	int   status;
	pid_t pid = fork(); /* Creates the child process */
	if (pid == -1) {
		fprintf(stderr, "Error while compilig: fork: %s", strerror(errno));
		fprintf(stderr, "Aborting....");
		abort();
	} else if (pid == 0) { /* Child process */
		int ret = execv(c.compiler_path, (char *const *) args);
		if (ret == -1) { /* Somehting went wrong */
			fprintf(stderr, "Error while compilig: execv: %s",
				strerror(errno));
			fprintf(stderr, "Aborting....");
			abort();
		}

		assert(0); /* Shouldn't exectue this  */
	} else {	   /* Parent process */
		pid_t child_pid =
			waitpid(pid, &status, 0); /* waits the child process execute */
		if (child_pid == -1) {
			/* ALERT the user that the compiled code doesn't work */
			fprintf(stderr, "Error while compilig: waitpid: %s",
				strerror(errno));

			fprintf(stderr, "Aborting....");
			abort();
		}
	}

	return status;
}

/* execute: Executes the gived command. */
static int execute(const char *command, const char *args[50])
{
	int   status;
	pid_t pid = fork(); /* Creates the child process */
	if (pid == -1) {
		fprintf(stderr, "Error while testing: fork: %s", strerror(errno));
		fprintf(stderr, "Aborting....");
		abort();
	} else if (pid == 0) { /* Child process */
		int ret = execv(command, (char *const *) args);
		if (ret == -1) { /* Somehting went wrong */
			fprintf(stderr, "Error while testing: execl: %s",
				strerror(errno));
			fprintf(stderr, "Aborting....");
			abort();
		}

		assert(0); /* Shouldn't exectue this  */
	} else {	   /* Parent process */
		pid_t child_pid =
			waitpid(pid, &status,
				0); /* waits the child process finished its excecution */
		if (child_pid == -1) {
			fprintf(stderr, "Error while testing: waitpid: %s",
				strerror(errno));
			fprintf(stderr, "Aborting....");
			abort();
		}
	}

	return status;
}

/* add_args: Adds arguments to the buffer of arguments */
static size_t add_args(char **args_buf_ptr, const char *some_args, size_t nargs)
{
	size_t n;
	n = strlen(some_args);

	for (size_t i = 0; i < n; i++) {
		size_t j;
		args[nargs] = *args_buf_ptr;
		for (j = 0; i < n && some_args[i] != ' '; j++)
			args[nargs][j] = some_args[i++];
		args[nargs][j] = '\0'; /* Null termined */
		*args_buf_ptr += j + 1;
		nargs++;
	}

	return nargs;
}

/* unittest_recompile_without_tests: Re-compiles the source file into an executable
 * without including any test files. */
void unittest_recompile_without_tests(const C c)
{
	size_t nargs;

	/* Reset the buffer */
	memset(args, 0, sizeof(args));
	memset(args_buf, 0, sizeof(args_buf));

	char *args_buf_ptr = args_buf;
	nargs		   = add_args(&args_buf_ptr, c.compiler, 0);
	nargs		   = add_args(&args_buf_ptr, unittest_file, nargs);

#ifndef NDEBUG
	char	       libpath[100];
	extern uint8_t is_root_folder;

	memset(libpath, 0, sizeof(libpath));
	if (is_root_folder) strcpy(libpath, (LIB_UNITTEST) + 3);
	else strcpy(libpath, LIB_UNITTEST);

	nargs = add_args(&args_buf_ptr, libpath, nargs);
#else
	nargs = add_args(&args_buf_ptr, LIB_UNITTEST, nargs);
#endif

	nargs = add_args(&args_buf_ptr, "-o", nargs);
	nargs = add_args(&args_buf_ptr, unittest_outfile, nargs);
	nargs = add_args(&args_buf_ptr, "-ltc", nargs);

	if (compile(c, (const char **) args) != 0) {
		fprintf(stderr, "Aborting.....\n");
		abort();
	}
}

/* unittest_rerun_with_tests: Re-executes the test program with the tests files already
 * loaded. */
void unittest_rerun_with_tests(void)
{
	size_t nargs = 0;
	char   command[50], *args_buf_ptr = args_buf;

	/* Reset the buffer */
	memset(args, 0, sizeof(args));
	memset(args_buf, 0, sizeof(args_buf));
	memset(command, 0, sizeof(command));

	if (unittest_run_valgrind) {
		char executable[50];

		memset(executable, 0, sizeof(executable));
		strcpy(command, "/usr/bin/");
		strcat(command, VALGRIND);
		nargs = add_args(&args_buf_ptr, VALGRIND, 0);
		nargs = add_args(&args_buf_ptr, VALGRIND_FLAGS, nargs);
		strcpy(executable, "./");
		strcat(executable, unittest_outfile);
		nargs = add_args(&args_buf_ptr, executable, nargs);
	} else {
		strcpy(command, "./");
		strcat(command, unittest_outfile);
		nargs = add_args(&args_buf_ptr, command, nargs);
	}

	/* Exectues with the loaded tests */
	if (execute(command, (const char **) args) != 0) {
		fprintf(stderr, "Aborting.....\n");
		abort();
	}
}

/* unittest_recompile_with_tests: Re-compiles and links the source files including the
   tests files,
   Re-producing a new executable. */
void unittest_recompile_with_tests(const C c)
{
	char   output[MAX_AMOUNT_OF_FILES][255];
	size_t n_outputs = 0;
	size_t nargs;

	/* TODO: Chacnge the buggy str functions */
	create_obj_directory(); /* Create the object directory  */
	memset(output, 0, sizeof(output));

	while (unittest_head_files != NULL) {
		/* Catch the object file */
		strcat(output[n_outputs], unittest_objdir);
		strcat(output[n_outputs], unittest_head_files->filename);

		/* Change the last character test.c -> test.o */
		output[n_outputs][strlen(output[n_outputs]) - 1] = 'o';

		/* Check if there were changes */
		if (unittest_needs_update(unittest_head_files->date_hashed)) {
			char source[255];
			memset(source, 0, 255);

			strcat(source, unittest_testdir);
			strcat(source, unittest_head_files->filename);

			/* Attach the arguments */
			memset(args, 0, sizeof(args));
			memset(args_buf, 0, sizeof(args_buf));

			char *args_buf_ptr = args_buf;
			nargs		   = add_args(&args_buf_ptr, c.compiler, 0);
			nargs = add_args(&args_buf_ptr, c.compiler_flags, nargs);
			nargs = add_args(&args_buf_ptr, "-c", nargs);
			nargs = add_args(&args_buf_ptr, source, nargs);
			nargs = add_args(&args_buf_ptr, "-o", nargs);
			nargs = add_args(&args_buf_ptr, output[n_outputs], nargs);

			LOG("[COMPILING] %s -o %s\n", source, output[n_outputs]);
			if (compile(c, (const char **) args) != 0) {
				/* TODO: Deal with the dynamic memory */
				fprintf(stderr, "ERROR: While compiling: %s -o %s\n",
					unittest_head_files->filename, output[n_outputs]);

				/* Free all dynamic memory before exit */
				do {
					unittest_map_free(
						(const uint8_t *)
							unittest_head_files->filename,
						strlen(unittest_head_files->filename));

					F *prev		    = unittest_head_files;
					unittest_head_files = unittest_head_files->next;
					free(prev);
				} while (unittest_head_files);

#ifndef NDEBUG
				fprintf(stderr, "TESTING: Exiting with SUCCESS.....\n");
				/* Because we are testing */
				exit(EXIT_SUCCESS);
#else
				fprintf(stderr, "Exiting with FAILURE.....\n");
				exit(EXIT_FAILURE);
#endif
			}
		}

		n_outputs++;
		unittest_map_free((const uint8_t *) unittest_head_files->filename,
				  strlen(unittest_head_files->filename));

		F *prev		    = unittest_head_files;
		unittest_head_files = unittest_head_files->next;
		free(prev);
	}

	/* Reset the buffer */
	memset(args, 0, sizeof(args));
	memset(args_buf, 0, sizeof(args_buf));

	char *args_buf_ptr = args_buf;

	/* Prepare the argments */
	nargs = add_args(&args_buf_ptr, c.compiler, 0);
	nargs = add_args(&args_buf_ptr, c.compiler_flags, nargs);
	nargs = add_args(&args_buf_ptr, "-D UNITTEST_RECOMPILE=0", nargs);
	nargs = add_args(&args_buf_ptr, unittest_file,
			 nargs); /* File it already has already the base dir */

	/* Put all the object files */
	for (size_t i = 0; i < n_outputs; i++)
		nargs = add_args(&args_buf_ptr, output[i], nargs);

#ifndef NDEBUG /* For debugin the framework */
	char	       libpath[100];
	extern uint8_t is_root_folder;

	memset(libpath, 0, sizeof(libpath));
	if (is_root_folder) strcpy(libpath, (LIB_UNITTEST) + 3);
	else strcpy(libpath, LIB_UNITTEST);

	nargs = add_args(&args_buf_ptr, libpath, nargs);
#else
	nargs = add_args(&args_buf_ptr, LIB_UNITTEST, nargs);
#endif

	nargs = add_args(&args_buf_ptr, "-o", nargs);
	nargs = add_args(&args_buf_ptr, unittest_outfile, nargs);
	nargs = add_args(&args_buf_ptr, "-ltc", nargs);

	if (strcmp(unittest_extra_flags,
		   unittest_basedir)) /* If the user add extra flags */
		nargs = add_args(&args_buf_ptr, unittest_extra_flags, nargs);

	/* Compile with loaded tests */
	if (compile(c, (const char **) args) != 0) {
		fprintf(stderr, "ERROR Linking: Aborting.....\n");
		abort();
	}
}

#undef C
#undef F
