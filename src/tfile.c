/*!
  @file unittest_tfile.c
  @brief These code implementations manage the process of test files by collecting their creation dates.
  By comparing the dates, the code can determine if a test file needs to be updated, and then proceed to
  compile the update accordingly.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_def.h"
#include "../include/unittest_dir.h"
#include "../include/unittest_hashdates.h"
#include "../include/unittest_tfile.h"

#include <assert.h> /* assert() */
#include <fcntl.h>  /* create() */
#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h> /* stat() */
#include <time.h>     /* ctime() */
#include <trycatch.h> /* throw() */
#include <unistd.h>   /* access() */

size_t unittest_tfile_count = 0;
_Static_assert(MAX_AMOUNT_OF_TEST_FILES == 128, "Should be 128 test files at max");
UnitTestFile unittest_tfiles[MAX_AMOUNT_OF_TEST_FILES];

/* unittest_file_already_included: Checks if a file has been already included. */
bool unittest_file_already_included(const char *file)
{
	assert(file != NULL);

	for (size_t i = 0; i < unittest_tfile_count; i++)
		if (strcmp(unittest_tfiles[i].name, file) == 0)
			return true;
	return false;
}


/* unittest_include_tfile: This function includes a file with a given unittest_hashed_file
 * into a specific test directory. */
void unittest_include_tfile(UnitTestFile *tf)
{
	assert(tf != NULL && "Erro can't be null");

	/* First check if the directoy exist */
	unittest_check_testdir_exist();

	long h;
	char date[50], path[255];

	memset(path, 0, 255);
	strcat(path, unittest_testdir);
	strcat(path, tf->name);

	unittest_get_creation_date(path, date);
	h		= unittest_hash((const char *) date);
	tf->date_hashed = h;
}

/* unittest_include_files: Include the whole files. */
void unittest_include_files(void)
{
	assert(unittest_tfile_count > 0 && "At least one needs to be include");

	for (size_t i = 0; i < unittest_tfile_count; i++)
		unittest_include_tfile(&unittest_tfiles[i]);
}

/* unittest_tfile_needs_update: checks if a file needs to be updated based on its hashed
 * creation date.
 */
bool unittest_tfile_needs_update(const UnitTestFile *tf)
{
	size_t i;

	for (i = 0; i < unittest_amount_hashed_dates; i++)
		if (tf->date_hashed ==
		    unittest_hashed_dates[i]) { /* If there weren't chages return 0 */
			unittest_hashed_dates[i] =
				unittest_hashed_dates[unittest_amount_hashed_dates - 1];
			unittest_amount_hashed_dates--;
			return false;
		}
	return true;
}
