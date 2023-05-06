/*!
  @file unittest_tfile.h
  @brief Defines the interface for managing test files. It includes the definition of the F struct,
  which represents a test file, as well as the maximum number of files and suits that can be stored.
  It also provides function prototypes for getting the creation time of a file and attaching a file
  to the test suite. The head_files variable is declared as extern to allow access to it from other modules.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_TESTFILE_INCLUDED
#define UNITTEST_TESTFILE_INCLUDED
#include <stdint.h>

#define MAX_AMOUNT_OF_FILES	     100
#define MAX_AMOUNT_OF_SUITS_IN_FILES 100

#define F			     TestFile

/* The struct that stores information about test files, including the filename and a hash
   of the file creation date. */
typedef struct F F;
struct F {
	const char *filename;
	long	    date_hashed;
	F	   *next;
};

/* A  pointer to a linked list of F structs representing files that will be used for
 * testing. */
extern F *head_files;

/* put_new_dates: Puts new creation/modification dates of the test files in the file. */
extern void put_new_dates(const char *test_dir, const char *filename);

/* get_prev_dates: Gets the previous modification dates of the test files from a file. */
extern void get_prev_dates(const char *test_dir, const char *filename);

/* needs_update: checks if a file needs to be updated based on its hashed creation date.
 */
extern uint8_t needs_update(long date_hashed);

/* get_creation_date: This function gets the creation time of a file located at a given
   path
   and stores it as a string in the date parameter. */
extern void get_creation_date(const char *path_file, char *date);

/* include: This function includes a file with a given filename into a specific test
 * directory. */
extern void include(const char *test_dir, const char *filename);

#undef F
#endif
