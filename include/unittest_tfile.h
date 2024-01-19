/*!
  @file unittest_tfile.h
  @brief Defines the interface for managing test files. It includes the definition of the UnitTestFile struct,
  which represents a test file, as well as the maximum number of files and suits that can be stored.
  It also provides function prototypes for getting the creation time of a file and attaching a file
  to the test suite.
  The unittest_head_files variable is declared as extern to allow access to it from other modules.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_TESTFILE_INCLUDED
#define UNITTEST_TESTFILE_INCLUDED
#include <stdint.h>

#include "unittest_def.h"
#include <stdbool.h>
#include <stddef.h>

/* The struct that stores information about test files, including the filename and a hash
   of the file creation date. */
typedef struct {
	const char *filename;
	long	    date_hashed;
} UnitTestFile;

#define INCLUDE_SUIT(filename, ...) unittest_tfiles[unittest_tfile_count++].filename = filename
#define INCLUDE_TESTCASE(filename, ...) unittest_tfiles[unittest_tfile_count++].filename = filename

extern size_t unittest_tfile_count;
extern UnitTestFile unittest_tfiles[MAX_AMOUNT_OF_TEST_FILES];

/* unittest_include_tfile: This function includes a test file with a given filename into a specific
 * test directory. */
extern void unittest_include_tfile(const char *filename);

/* unittest_tfile_needs_update: checks if a file needs to be updated based on its hashed
 * creation date.
 */
extern bool unittest_tfile_needs_update(const UnitTestFile *tfile);


/* unittest_get_prev_dates: Gets the previous modification dates of the test files from a
 * file. */
extern void unittest_get_prev_dates(void);



/* unittest_put_new_dates: Puts new creation/modification dates of the test files in the
 * file. */
extern void unittest_put_new_dates(void);


#endif
