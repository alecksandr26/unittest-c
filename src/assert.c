/*!
  @file unittest_assert.h
  @brief The assertions macros for the testcases.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_assert.h"
#include "../include/unittest_debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define F UnitTestInfoFailed

/* Sime implemention of an assert */
void unittest_print_faild_test(F *info)
{
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

#undef F
