/*!
  @file unittest_assert.h
  @brief The assertions macros for the testcases.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include <stdlib.h>
#include <unistd.h>
#include <except.h>

#include "../include/unittest.h"
#include "../include/unittest_assert.h"

/* Sime implemention of an assert */
void unittest_print_faild_test(const char *expr, TestCase *tcase,
			 int line, const char *msg)
{
	
	
	/* not aboring the program */
}


