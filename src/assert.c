/*!
  @file assert.c
  @brief The source code for the unittest_assert.h component.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_def.h"
#include "../include/unittest_assert.h"
#include "../include/unittest_debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

_Static_assert(MAX_AMOUNT_OF_TESTS_IN_TESTCASES == 128, "This should 128 testscases");
_Static_assert(MAX_AMOUNT_OF_TESTCASES == 1024, "This should 1024 testscases");
_Static_assert(MAX_AMOUNT_OF_TESTS_INFO_FAILD == 131072, "This initialy should be 1024 * 128");

UnitTestInfoFailed *infofails[MAX_AMOUNT_OF_TESTS_INFO_FAILD];

/* unittest_print_faild_test: This function prints the information for a failed test,
   including the expression, message, test name, testcase name and filename. */
void unittest_print_faild_test(UnitTestInfoFailed *info)
{
	assert(info != NULL && "Can't be null");
	
	LOG("==========================================================================="
	    "===========\n");

	LOG("FAIL:\t\t%s\t\t(%s.%s)\n", info->test, info->unitcase, info->test);
	LOG("---------------------------------------------------------------------------"
	    "-----------\n");
	LOG("Traceback...\n");
	LOG("\tFile \"%s\", line %i, in %s\n", info->file, info->line, info->test);
	if (info->msg != NULL)
		LOG("AssertionError:\t \"%s\",\t\"%s\" \n\n", info->expr, info->msg);
	else LOG("AssertionError:\t \"%s\"\n\n", info->expr);
}
