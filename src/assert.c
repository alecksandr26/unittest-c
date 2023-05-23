/*!
  @file unittest_assert.h
  @brief The assertions macros for the testcases.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_assert.h"

#include <except.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define F UnitTestInfoFailed

/* Fetch the out stream */
extern FILE *unittest_stdout;

/* Sime implemention of an assert */
void unittest_print_faild_test(F *info)
{
	fprintf(unittest_stdout, "==========================================================================="
		"===========\n");
	fprintf(unittest_stdout, "FAIL:\t\t%s\t\t(%s.%s)\n", info->test, info->unitcase, info->test);
	fprintf(unittest_stdout, "---------------------------------------------------------------------------"
		"-----------\n");
	fprintf(unittest_stdout, "Traceback...\n");
	fprintf(unittest_stdout, "\tFile \"%s\", line %i, in %s\n", info->file, info->line, info->test);
	if (info->msg != NULL)
		fprintf(unittest_stdout, "AssertionError:\t \"%s\",\t\"%s\" \n\n", info->expr, info->msg);
	else fprintf(unittest_stdout, "AssertionError:\t \"%s\"\n\n", info->expr);
}

#undef F
