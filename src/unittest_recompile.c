/*!
  @file unittest_recompile.c
  @brief This module contains implementations for recompiling the main executable
  program with or without test files and for rerunning the program after recompilation.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_recompile.h"

#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <except.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#define C CompilerContex

#include "../include/unittest_tfile.h"
#define F TestFile

#include "../include/unittest_map.h"

Except UnittestErrorCreatingDir = {
	"Error creating the object dir \"OBJ_DIR\" at \"TEST_DIR\""};

char *args[50];	      /* Max 50 arguments */
char  args_buf[2048]; /* Buffer where the args will be allocated */

static void create_obj_directory(const char *test_dir, const char *obj_dir)
{
	const size_t len = strlen(test_dir) + strlen(obj_dir);

	char path[len];

	memset(path, 0, len);
	strcat(path, test_dir);
	strcat(path, obj_dir);

	/* First check if the directoy exist */
	DIR *dir = opendir(path);
	if (dir) {
		closedir(dir);
		return; /* Already exist */
	}

	closedir(dir);
	if (mkdir(path, 0775) != 0) throw_except(UnittestErrorCreatingDir);
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
			fprintf(stderr, "Error while compilig: execv: %s", strerror(errno));
			fprintf(stderr, "Aborting....");
			abort();
		}

		assert(0); /* Shouldn't exectue this  */
	} else {	   /* Parent process */
		pid_t child_pid =
			waitpid(pid, &status, 0); /* waits the child process execute */
		if (child_pid == -1) {
			fprintf(stderr, "Error while compilig: waitpid: %s", strerror(errno));
			fprintf(stderr, "Aborting....");
			abort();
		}
	}

	return status;
}

/* add_args: Adds arguments to the buffer of arguments */
static size_t add_args(char *args[50], const char *some_args, char args_buffer[1024],
		       size_t nargs)
{
	size_t n;
	n = strlen(some_args);

	static size_t ibuf = 0; /* The first time will be 0 */
	for (size_t i = 0; i < n; i++) {
		size_t j;
		args[nargs] = args_buffer + ibuf;
		for (j = 0; i < n && some_args[i] != ' '; j++)
			args[nargs][j] = some_args[i++];
		args[nargs][j] = '\0'; /* Null termined */
		ibuf += j + 1;
		nargs++;
	}

	return nargs;
}

/* execute: Executes the gived program. */
static int execute(const char *outfile)
{
	int   status;
	pid_t pid = fork(); /* Creates the child process */
	if (pid == -1) {
		fprintf(stderr, "Error while testing: fork: %s", strerror(errno));
		fprintf(stderr, "Aborting....");
		abort();
	} else if (pid == 0) { /* Child process */
		char path[255];
		memset(path, 0, 255);
		strcat(path, "./");
		strcat(path, outfile);
		int ret = execl(path, path, NULL);
		if (ret == -1) { /* Somehting went wrong */
			fprintf(stderr, "Error while testing: execl: %s", strerror(errno));
			fprintf(stderr, "Aborting....");
			abort();
		}

		assert(0); /* Shouldn't exectue this  */
	} else {	   /* Parent process */
		pid_t child_pid =
			waitpid(pid, &status, 0); /* waits the child process execute */
		if (child_pid == -1) {
			fprintf(stderr, "Error while testing: waitpid: %s", strerror(errno));
			fprintf(stderr, "Aborting....");
			abort();
		}
	}

	return status;
}

/* recompile_without_tests: Re-compiles the source file into an executable without
 * including any test files. */
void recompile_without_tests(const C c, const char *file, const char *outfile)
{
	size_t nargs;

	/* Recompile without tests */
	memset(args, 0, sizeof(args));

	nargs = add_args(args, c.compiler, args_buf, 0);
	nargs = add_args(args, file, args_buf, nargs);
	nargs = add_args(args, LIB_UNITTEST, args_buf, nargs);
	nargs = add_args(args, "-o", args_buf, nargs);
	nargs = add_args(args, outfile, args_buf, nargs);
	nargs = add_args(args, "-lexcept", args_buf, nargs);

	if (compile(c, (const char **) args) != 0) {
		fprintf(stderr, "Aborting.....\n");
		abort();
	}
}

/* rerun_with_tests: Re-executes the test program with the tests files already loaded. */
void rerun_with_tests(const char *outfile)
{
	/* Exectues with the loaded tests */
	if (execute(outfile) != 0) {
		fprintf(stderr, "Aborting.....\n");
		abort();
	}
}

/* recompile_with_tests: Re-compiles and links the source files including the tests files,
   Re-producing a new executable. */
void recompile_with_tests(const C c, const char *test_dir, const char *obj_dir,
			  const char *file, const char *outfile)
{
	char   output[MAX_AMOUNT_OF_FILES][255];
	size_t n_outputs = 0;
	size_t nargs;

	create_obj_directory(test_dir, obj_dir); /* Create the object file  */

	memset(output, 0, sizeof(output));

	while (head_files != NULL) {
		/* Catch the object file */
		strcat(output[n_outputs], test_dir);
		strcat(output[n_outputs], obj_dir);
		strcat(output[n_outputs], head_files->filename);

		/* Change the last character test.c -> test.o */
		output[n_outputs][strlen(output[n_outputs]) - 1] = 'o';

		/* Check if there were changes */
		if (needs_update(head_files->date_hashed)) {
			char source[255];

			memset(source, 0, 255);

			/* TODO: Clean the outputs */
			strcat(source, test_dir);
			strcat(source, head_files->filename);

			/* Attach the arguments */
			memset(args, 0, sizeof(args));
			nargs = add_args(args, c.compiler, args_buf, 0);
			nargs = add_args(args, c.compiler_flags, args_buf, nargs);
			nargs = add_args(args, "-c", args_buf, nargs);
			nargs = add_args(args, source, args_buf, nargs);
			nargs = add_args(args, "-o", args_buf, nargs);
			nargs = add_args(args, output[n_outputs], args_buf, nargs);

			printf("[COMPILING] %s -o %s\n", source, output[n_outputs]);
			if (compile(c, (const char **) args) != 0) {
				fprintf(stderr, "Aborting.....\n");
				abort();
			}
		}

		n_outputs++;
		unittest_map_free((const uint8_t *) head_files->filename,
				  strlen(head_files->filename));
		F *prev	   = head_files;
		head_files = head_files->next;
		free(prev);
	}

	/* Reset the buffer */
	memset(args, 0, sizeof(args));

	/* Prepare the argments */
	nargs = add_args(args, c.compiler, args_buf, 0);
	nargs = add_args(args, "-D UNITTEST_RECOMPILE=0", args_buf, nargs);
	nargs = add_args(args, file, args_buf, nargs);

	/* Put all the object files */
	for (size_t i = 0; i < n_outputs; i++)
		nargs = add_args(args, output[i], args_buf, nargs);

	/* TODO: For the debugin purpuse for the moment to be able to compile
	 * example/test.c */
	nargs = add_args(args, LIB_UNITTEST, args_buf, nargs);
	nargs = add_args(args, "-o", args_buf, nargs);
	nargs = add_args(args, outfile, args_buf, nargs);
	nargs = add_args(args, "-lexcept", args_buf, nargs);

	/* Compile with loaded tests */
	if (compile(c, (const char **) args) != 0) {
		
		fprintf(stderr, "Aborting.....\n");
		abort();
	}
}

#undef C
#undef F
