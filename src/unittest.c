/*!
  @file unittest.c
  @brief A set of macros to create new testcases or thats the idea.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include <stddef.h>
#include <stddef.h>
#include <stdarg.h>
#include <except.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include "../include/unittest.h"
#include "../include/atom.h"

#define TF TestCaseFrame
#define TC TestCase
#define F TestFile
#define S Suit
#define C CompilerContex

/* Keep track on the files */
typedef struct F F;
struct F {
	const char *filename;
	long hash;
	F *next;
};


/* To keep track from all the created tests */
TC *head_tc = NULL;
F *head_files = NULL;
Except UnittestNotEnoughMemory = {"Not enough memory for the heap allocating"},
	UnittestErrorOpeningFile = {"Error opening a file the hashed dates binary file"},
	UnittestErrorCreatingFile = {"Error creating the hashed dates binary file"},
	UnittestErrorReadingFile = {"Error while reading the hashed dates binary file"},
	UnittestErrorCreatingDir = {"Error creating the dir where the objects files  will be allocated"};

/* Dealing with the hashed dates and identify which file needs to be recompiled */
uint8_t dumped = 0;
size_t amount_hashed_dates = 0;
long hashed_dates[MAX_AMOUNT_OF_FILES];
char files[MAX_AMOUNT_OF_FILES][255];

/* Fetchs the last update  */
void get_file_creation_time(const char *path, char *date)
{
	struct stat attr;
	
	assert(date != NULL && path != NULL && "You can't pass null arguemnt");
	
	stat(path, &attr);
	sprintf(date, "Last modified time: %s", ctime(&attr.st_mtime));
}


static void dump_hashed_dates_to_atoms(const char *test_dir, const char *filename)
{
	FILE *fp;
	const size_t len = strlen(test_dir) + strlen(filename);
	
	if (dumped !=  0) return; /* Finish the function */
	dumped = 1;

	char path[len];
	
	memset(path, 0, len);
	strcat(path, test_dir);
	strcat(path, filename);

	if (access(path, F_OK) == -1) { /* Doens't exist the file */
		if (creat(path, 0664) == -1)
			raise(UnittestErrorCreatingFile);
		return;
	}
	
	if ((fp = fopen(path, "rb")) == NULL )
		raise(UnittestErrorOpeningFile);
	
	/* Read the hashed binaries*/
	if (fread(&amount_hashed_dates, sizeof(size_t), 1, fp) != sizeof(size_t))
		raise(UnittestErrorReadingFile);

	if (fread(hashed_dates, sizeof(long), amount_hashed_dates, fp) \
	    != sizeof(long) * amount_hashed_dates)
		raise(UnittestErrorReadingFile);
	
	fclose(fp);

	/* Hash each of one */
	for (size_t i = 0; i < amount_hashed_dates; i++)
		Atom_int(hashed_dates[i]);
}

static void create_obj_directory(const char *test_dir, const char *obj_dir)
{
	const size_t len = strlen(test_dir) + strlen(obj_dir);

	char path[len];

	memset(path, 0, len);
	strcat(path, test_dir);
	strcat(path, obj_dir);
	
	/* First check if the directoy exist */
	 DIR* dir = opendir(path);
	 if (dir) return;	/* Already exist */

	 if (mkdir(path, 0775) != 0)
		 raise(UnittestErrorCreatingDir);
}

void recompile(const CompilerContex c, const char *test_dir,
	       const char *hashed_file_name, const char *obj_dir)
{
	create_obj_directory(test_dir, obj_dir);	/* Create the directory */
	dump_hashed_dates_to_atoms(test_dir, hashed_file_name); /* Load the previous date hashed binaries */

	while (head_files != NULL) {
		/* Recompile the file */
		printf("%s\n", head_files->filename);
		
		head_files = head_files->next;
	}
}

void attach_file(const char *filename)
{
	assert(filename != NULL && "Erro can't be null");
	long h;
	char date[50];
	
	/* Recompile the program if it is different size */
	get_file_creation_time(filename, date);
	h = Atom_hash(date);

	F *new_file;
	if ((new_file = malloc(sizeof(F))) == NULL)
		raise(UnittestNotEnoughMemory);
	
	new_file->hash = h;
	new_file->next = head_files;
	head_files = new_file;
}

void link_tcase(TC *tc)
{
	tc->next = head_tc;
	head_tc = tc;
}

void link_suit(S *suit)
{
	for (size_t i = 0; i < suit->amount; i++)
		link_tcase(suit->tcase[i]);
}

void run_tests(void)
{
	assert(head_tc != NULL && "Should be at least one test");
	
	/* Execute each testcase */
	clock_t start_time = clock();
	size_t count_tests = 0;
	while (head_tc != NULL) {
		head_tc->test(head_tc);
		count_tests += head_tc->amount;
		/* Move to the next test */
		head_tc = head_tc->next;
	}

	clock_t end_time = clock();
	printf("\n");
	puts("----------------------------------------------------------------------");
	printf("Ran %zu test in %fs\n", count_tests, (double)(end_time - start_time) / CLOCKS_PER_SEC);

	printf("\nOk\n");
	
}


#undef S
#undef TF
#undef TC
#undef F
#undef C
