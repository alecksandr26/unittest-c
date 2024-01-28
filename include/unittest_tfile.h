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
#include "unittest_def.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* The struct that stores information about test files, including the filename and a hash
   of the file creation date. */
typedef struct {
	char *name;
	long  date_hashed;
} UnitTestFile;

#define INCLUDE_SUIT(filename, ...)		\
	do {								\
		if (!unittest_file_already_included(filename))		\
			unittest_tfiles[unittest_tfile_count++].name = filename; \
	} while (0)

#define INCLUDE_TESTCASE(filename, ...)					\
	do {								\
		if (!unittest_file_already_included(filename))		\
			unittest_tfiles[unittest_tfile_count++].name = filename; \
	} while (0)

extern size_t	    unittest_tfile_count;
extern UnitTestFile unittest_tfiles[MAX_AMOUNT_OF_TEST_FILES];

/* unittest_file_already_included: Checks if a file has been already included. */
extern bool unittest_file_already_included(const char *file);

/* unittest_include_files: Include the whole files. */
extern void unittest_include_files(void);

/* unittest_tfile_needs_update: checks if a file needs to be updated based on its hashed
 * creation date.
 */
extern bool unittest_tfile_needs_update(const UnitTestFile *tfile);

#endif
