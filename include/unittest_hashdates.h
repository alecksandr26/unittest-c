/*
  @file unittest_hashdates.h
  @brief This is the component in charge of manipulating the hash dates from the testfiles, and to hash
  the dates of the files.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License.
*/

#ifndef HASH_DATES_INCLUDED
#define HASH_DATES_INCLUDED

#include "unittest_def.h"

#include <stddef.h>

extern size_t unittest_amount_hashed_dates;
extern long   unittest_hashed_dates[MAX_AMOUNT_OF_TEST_FILES];

/* unittest_hash: To hash some string and return some random unsinged integer */
extern unsigned long unittest_hash(const char *data);

/* unittest_get_creation_date: This function gets the creation time of a file located at a
   given path and stores it as a string in the date parameter. */
extern void unittest_get_creation_date(const char *path_file, char *date);

/* unittest_put_new_dates: Puts new creation/modification dates of the test files in the
 * file. */
extern void unittest_put_new_dates(void);

/* unittest_get_prev_dates: Gets the previous modification dates of a file in a specific
 * directory.
 */
extern void unittest_get_prev_dates(void);

#endif
