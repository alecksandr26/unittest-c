/*!
  @file unittest.c
  @brief A set of macros to create new testcases or thats the idea.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest.h"

#include "../include/unittest_map.h"

#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <except.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>

#define TF TestCaseFrame
#define TC TestCase
#define F  TestFile
#define S  Suit
#define C  CompilerContex

/* TODO: For the moment to be able to compile the exmaple/test.c */
#define LIB_UNITTEST "../lib/libunittest.a"

/* Keep track on the files */
typedef struct F F;
struct F {
	const char *filename;
	long	    hash;
	F	   *next;
};

/* To keep track from all the created tests */
TC    *head_tc			 = NULL;
F     *head_files		 = NULL;
Except UnittestNotEnoughMemory	 = {"Not enough memory for the heap allocating"},
       UnittestErrorOpeningFile	 = {"Error opening a file the hashed dates binary file"},
       UnittestErrorCreatingFile = {"Error creating the hashed dates binary file"},
       UnittestErrorReadingFile	 = {"Error while reading the hashed dates binary file"},
       UnittestErrorCreatingDir =
	       {"Error creating the dir where the objects files  will be allocated"},
       UnittestErrorTestBaseDoesntExist = {"The test base directory doesn't exist"},
       UnittestErrorWrittingFile	= {"Error while writting some file"};

/* Dealing with the hashed dates and identify which file needs to be recompiled */
uint8_t dumped			= 0;
size_t	amount_hashed_dates	= 0;
size_t	new_amount_hashed_dates = 0;
long	hashed_dates[MAX_AMOUNT_OF_FILES];
long	new_hashed_dates[MAX_AMOUNT_OF_FILES];
char	files[MAX_AMOUNT_OF_FILES][255];
char   *args[50];	/* Max 50 arguments */
char	args_buf[1024]; /* Buffer where the args will be allocated */

/* Fetchs the last update  */
void get_file_creation_time(const char *path, char *date)
{
	struct stat attr;

	assert(date != NULL && path != NULL && "You can't pass null arguemnt");

	stat(path, &attr);
	sprintf(date, "Last modified time: %s", ctime(&attr.st_mtime));
}

static void dump_hashed_dates_to_buffer(const char *test_dir, const char *filename)
{
	FILE	    *fp;
	const size_t len = strlen(test_dir) + strlen(filename);

	if (dumped != 0) return; /* Finish the function */
	dumped = 1;

	char path[len];

	memset(path, 0, len);
	strcat(path, test_dir);
	strcat(path, filename);

	if (access(path, F_OK) == -1) { /* Doens't exist the file */
		if (creat(path, 0664) == -1) throw_except(UnittestErrorCreatingFile);
		return;
	}

	if ((fp = fopen(path, "rb")) == NULL) throw_except(UnittestErrorOpeningFile);

	/* Read the hashed binaries*/
	if (fread(&amount_hashed_dates, sizeof(size_t), 1, fp) != 1)
		throw_except(UnittestErrorReadingFile);

	if (fread(hashed_dates, sizeof(long), amount_hashed_dates, fp) !=
	    amount_hashed_dates)
		throw_except(UnittestErrorReadingFile);

	fclose(fp);
}

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

/* check_changes: Return 1 if it finds the date hashed otherwise return 0 */
static uint8_t check_changes(long h)
{
	size_t i;

	for (i = 0; i < amount_hashed_dates; i++)
		if (h == hashed_dates[i]) { /* If there weren't chages return 0 */
			hashed_dates[i] = hashed_dates[amount_hashed_dates - 1];
			amount_hashed_dates--;
			return 0;
		}
	return 1;
}

/* parse_args: To parse the arguments for the compilation and return the amount of
 * arguments*/
static size_t parse_args(char *args[50], const char *some_args, char args_buffer[1024],
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

/* compile: Compiles something running a child process and returns it status */
static int compile(const CompilerContex c, const char *args[50])
{
	int   status;
	pid_t pid = fork(); /* Creates the child process */
	if (pid == -1) {
		fprintf(stderr, "Error while compilig: %s", strerror(errno));
		fprintf(stderr, "Aborting....");
		abort();
	} else if (pid == 0) { /* Child process */
		int ret = execv(c.compiler_path, (char *const *) args);
		if (ret == -1) { /* Somehting went wrong */
			fprintf(stderr, "Error while compilig: %s", strerror(errno));
			fprintf(stderr, "Aborting....");
			abort();
		}

		assert(0); /* Shouldn't exectue this  */
	} else {	   /* Parent process */
		pid_t child_pid =
			waitpid(pid, &status, 0); /* waits the child process execution */
		if (child_pid == -1) {
			fprintf(stderr, "Error while compilig: %s", strerror(errno));
			fprintf(stderr, "Aborting....");
			abort();
		}
	}

	return status;
}

/* dump_hashed_date_to_file: Rewrite the file */
static void dump_hashed_dates_to_file(const char *test_dir, const char *filename)
{
	FILE	    *fp;
	const size_t len = strlen(test_dir) + strlen(filename);
	char	     path[len];

	memset(path, 0, len);
	strcat(path, test_dir);
	strcat(path, filename);

	if (access(path, F_OK) == -1) /* Doens't exist the file */
		throw_except(UnittestErrorReadingFile);

	if ((fp = fopen(path, "wb")) == NULL) throw_except(UnittestErrorOpeningFile);

	/* Read the hashed binaries*/
	if (fwrite(&new_amount_hashed_dates, sizeof(size_t), 1, fp) != 1)
		throw_except(UnittestErrorWrittingFile);

	if (fwrite(new_hashed_dates, sizeof(long), new_amount_hashed_dates, fp) !=
	    new_amount_hashed_dates)
		throw_except(UnittestErrorWrittingFile);
	fclose(fp);
}

/* Run the binary with the tests activated */
static int test_execution(const char *outfile)
{
	int   status;
	pid_t pid = fork(); /* Creates the child process */
	if (pid == -1) {
		fprintf(stderr, "Error while testing: %s", strerror(errno));
		fprintf(stderr, "Aborting....");
		abort();
	} else if (pid == 0) { /* Child process */
		char path[255];
		memset(path, 0, 255);
		strcat(path, "./");
		strcat(path, outfile);
		int ret = execl(path, path, NULL);
		if (ret == -1) { /* Somehting went wrong */
			fprintf(stderr, "Error while testing: %s", strerror(errno));
			fprintf(stderr, "Aborting....");
			abort();
		}

		assert(0); /* Shouldn't exectue this  */
	} else {	   /* Parent process */
		pid_t child_pid =
			waitpid(pid, &status, 0); /* waits the child process execution */
		if (child_pid == -1) {
			fprintf(stderr, "Error while testing: %s", strerror(errno));
			fprintf(stderr, "Aborting....");
			abort();
		}
	}

	return status;
}

/* rerun: Re runs the program */
void rerun(const CompilerContex c, const char *file, const char *outfile)
{
	size_t nargs;

	if (test_execution(outfile) != 0) {
		fprintf(stderr, "Aborting.....\n");
		abort();
	}

	/* Recompile for last time to be able to detected changes */
	memset(args, 0, sizeof(args));

	/* Prepare the argments */
	nargs = parse_args(args, c.compiler, args_buf, 0);

	nargs = parse_args(args, file, args_buf, nargs);

	/* TODO: For the moment to be able to compile the exmaple/test.c */
	nargs = parse_args(args, LIB_UNITTEST, args_buf, nargs);

	nargs = parse_args(args, "-o", args_buf, nargs);
	nargs = parse_args(args, outfile, args_buf, nargs);

	nargs = parse_args(args, "-lexcept", args_buf, nargs);

	/* Last thing compile the binary file */
	if (compile(c, (const char **) args) != 0) {
		fprintf(stderr, "Aborting.....\n");
		abort();
	}
}

void recompile(const CompilerContex c, const char *test_dir, const char *hashed_file,
	       const char *obj_dir, const char *file, const char *outfile)
{
	/* First check if the directoy exist */
	DIR *dir;
	if ((dir = opendir(test_dir)) == NULL) {
		closedir(dir);
		throw_except(UnittestErrorTestBaseDoesntExist);
	}
	closedir(dir);
	
	create_obj_directory(test_dir,
			     obj_dir); /* Create the directory if doesn't exist */
	dump_hashed_dates_to_buffer(test_dir,
				    hashed_file); /* Load the previous dates hashed */

	char output[MAX_AMOUNT_OF_FILES][255];
	size_t n_outputs = 0;

	/* Parse arguments  */
	memset(args, 0, sizeof(args));
	size_t nargs = parse_args(args, c.compiler, args_buf, 0);
	nargs	     = parse_args(args, c.compiler_flags, args_buf, nargs);

	while (head_files != NULL) {
		/* Catch the object file */
		memset(output[n_outputs], 0, 255);
		strcat(output[n_outputs], test_dir);
		strcat(output[n_outputs], obj_dir);
		strcat(output[n_outputs], head_files->filename);

		/* Change the last character test.c -> test.o */
		output[n_outputs][strlen(output[n_outputs]) - 1] = 'o';

		/* Check if there were changes */
		if (check_changes(head_files->hash)) {
			char source[255];

			memset(source, 0, 255);

			/* TODO: Clean the outputs */
			strcat(source, test_dir);
			strcat(source, head_files->filename);

			/* Attach the arguments */
			nargs = parse_args(args, "-c", args_buf, nargs);
			nargs = parse_args(args, source, args_buf, nargs);
			nargs = parse_args(args, "-o", args_buf, nargs);
			nargs = parse_args(args, output[n_outputs], args_buf, nargs);

			printf("[COMPILING] %s -o %s\n", source, output[n_outputs]);
			if (compile(c, (const char **) args) != 0) {
				fprintf(stderr, "Aborting.....\n");
				abort();
			}


		}

		n_outputs++;
		unittest_map_free((const uint8_t *) head_files->filename,
				  strlen(head_files->filename));
		F *prev = head_files;
		head_files = head_files->next;
		free(prev);
	}

	/* Reset the buffer */
	memset(args, 0, sizeof(args));

	/* Prepare the argments */
	nargs = parse_args(args, c.compiler, args_buf, 0);

	nargs = parse_args(args, "-D UNITTEST_RECOMPILE=0", args_buf, nargs);
	nargs = parse_args(args, file, args_buf, nargs);

	/* Put all the object files */
	for (size_t i = 0; i < n_outputs; i++)
		nargs = parse_args(args, output[i], args_buf, nargs);

	/* TODO: For the debugin purpuse for the moment to be able to compile
	 * example/test.c */
	nargs = parse_args(args, LIB_UNITTEST, args_buf, nargs);

	nargs = parse_args(args, "-o", args_buf, nargs);
	nargs = parse_args(args, outfile, args_buf, nargs);

	nargs = parse_args(args, "-lexcept", args_buf, nargs);

	/* Compile with the the tests loaded */
	if (compile(c, (const char **) args) != 0) {
		fprintf(stderr, "Aborting.....\n");
		abort();
	}

	/* Sends the new hashed file */
	dump_hashed_dates_to_file(test_dir, hashed_file);
}

void attach_file(const char *test_dir, const char *filename)
{
	assert(filename != NULL && test_dir != NULL && "Erro can't be null");

	/* First check if the directoy exist */
	DIR *dir;
	if ((dir = opendir(test_dir)) == NULL) {
		closedir(dir);
		throw_except(UnittestErrorTestBaseDoesntExist);
	}
	closedir(dir);

	long h;
	char date[50], path[255];
	F *new_file;

	/* Map the name of the filename */
	const uint8_t *ptr =
		unittest_map_find((const uint8_t *) filename, strlen(filename));
	if (ptr != NULL) /* It is already include it */
		return;

	memset(path, 0, 255);
	strcat(path, test_dir);
	strcat(path, filename);

	get_file_creation_time(path, date);
	h = unittest_hash((const uint8_t *) date);
	
	if ((new_file = malloc(sizeof(F))) == NULL) throw_except(UnittestNotEnoughMemory);

	new_file->hash = h;
	/* Map the file name */
	new_file->filename =
		(char *) unittest_map((const uint8_t *) filename, strlen(filename));
	new_file->next = head_files;
	head_files     = new_file;

	/* Append the new hashed dates */
	new_hashed_dates[new_amount_hashed_dates++] = h;
}

void link_tcase(TC *tc)
{
	tc->next = head_tc;
	head_tc	 = tc;
}

void link_suit(S *suit)
{
	for (size_t i = 0; i < suit->amount; i++)
		link_tcase(suit->tcase[i]);
}

void run_tests(void)
{
	assert(head_tc != NULL && "Should be at least one test");
	size_t count_tests, success_test, failed_test;
	
	/* Execute each testcase */
	count_tests = success_test = failed_test = 0;
	clock_t start_time  = clock();
	while (head_tc != NULL) {
		/* Run the testscase */
		head_tc->test(head_tc);
		count_tests += head_tc->amount;
		success_test += head_tc->amount - head_tc->amount_failed;
		failed_test += head_tc->amount_failed;
		/* Move to the next test */
		head_tc = head_tc->next;
	}
	clock_t end_time = clock();
	printf("\n");
	puts("----------------------------------------------------------------------");
	if (failed_test == 0) {
		printf("Ran %zu test in %fs\n", count_tests,
		       (double) (end_time - start_time) / CLOCKS_PER_SEC);
		printf("\nOk \n\n");
	} else {
		printf("Ran %zu test in %fs succeed %zu failed %zu\n", count_tests,
		       (double) (end_time - start_time) / CLOCKS_PER_SEC, success_test, failed_test);
	}
		
}

#undef S
#undef TF
#undef TC
#undef F
#undef C
