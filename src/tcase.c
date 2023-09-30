/*!
  @file tcase.c
  @brief Defines a pointer to the head of the test cases list, provides a function to link a new
  test case to the list, and defines macros to handle the test cases and test functions.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_tcase.h"

#include <trycatch.h>
#define TC UnitTestCase
#define TE UnitTestCaseErrorInfo

/* unittest_head_tc: A pointer to the last linked test case. */
TC    *unittest_head_tc	 = NULL;
Except UnittestNoneTests = {"The testcase should have at least one test"};
TE     unittest_info_crashed_testcases[MAX_AMOUNT_OF_CRASHED_TESTCASES];

/* link_tcases: Links test case structures together for the testing process. */
void unittest_link_tcase(TC *tc)
{
	tc->next	 = unittest_head_tc;
	unittest_head_tc = tc;
}

#undef TC
#undef TE
