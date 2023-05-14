/*!
  @file unittest_tcase.c
  @brief Defines a pointer to the head of the test cases list, provides a function to link a new
  test case to the list, and defines macros to handle the test cases and test functions.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_tcase.h"
#define TC UnitTestCase

/* unittest_head_tc: A pointer to the last linked test case. */
TC *unittest_head_tc = NULL;

/* link_tcases: Links test case structures together for the testing process. */
void unittest_link_tcase(TC *tc)
{
	tc->next	 = unittest_head_tc;
	unittest_head_tc = tc;
}

#undef TC
