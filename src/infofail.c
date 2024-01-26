/*!
  @file infofail.c
  @brief The source code for the unittest_infofail.h component.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include <assert.h>

#include "../include/unittest_def.h"
#include "../include/unittest_debug.h"
#include "../include/unittest_infofail.h"
#include "../include/unittest_assert.h"


_Static_assert(MAX_AMOUNT_OF_TESTS_IN_TESTCASES == 128, "This should 128 testscases");
_Static_assert(MAX_AMOUNT_OF_TESTCASES == 1024, "This should 1024 testscases");
_Static_assert(MAX_AMOUNT_OF_INFO_FAILES == 1024, "This initialy should be 1024 * 128");

UnitTestInfoFailed *infofails[MAX_AMOUNT_OF_INFO_FAILES];


/* unittest_print_faild_testcase: This function prints the information for a failed test,
   including the expression, message, test name, testcase name and filename. */
void unittest_print_faild_testcase(UnitTestInfoFailed *info)
{
	assert(info != NULL && "Can't be null");

	/* Prints the asserts */
	for (size_t i = 0; i < info->number_failed_asserts; i++) {
		LOG(DIV_DOUBLE_LINE_STR);

		LOG("FAIL:\t\t%s\t\t(%s.%s)\n", info->failed_asserts[i].test, info->unitcase,
		    info->failed_asserts[i].test);
		LOG(DIV_LINE_STR);
		LOG("Traceback...\n");
		LOG("\tFile \"%s\", line %i, in %s\n", info->file, info->failed_asserts[i].line,
		    info->failed_asserts[i].test);
		if (info->failed_asserts[i].msg != NULL) {
			if (strlen(DIV_LINE_STR) < strlen(info->failed_asserts[i].expr) + 18) {
				LOG("AssertionError:\t \"%s\",\n", info->failed_asserts[i].expr);
				LOG("\t\t \"%s\" \n\n", info->failed_asserts[i].msg);
			} else {
				LOG("AssertionError:\t \"%s\",\t\"%s\" \n\n", info->failed_asserts[i].expr,
				    info->failed_asserts[i].msg);
			}
				
		}
		else LOG("AssertionError:\t \"%s\"\n\n", info->failed_asserts[i].expr);
	}

	/* Prints the expects */
	for (size_t i = 0; i < info->number_warning_expects; i++) {
		LOG(DIV_DOUBLE_LINE_STR);

		LOG("WARN:\t\t%s\t\t(%s.%s)\n", info->warning_expects[i].test, info->unitcase,
		    info->warning_expects[i].test);
		LOG(DIV_LINE_STR);
		LOG("Traceback...\n");
		LOG("\tFile \"%s\", line %i, in %s\n", info->file, info->warning_expects[i].line,
		    info->warning_expects[i].test);
		if (info->warning_expects[i].msg != NULL) {
			if (strlen(DIV_LINE_STR) < strlen(info->warning_expects[i].expr) + 18) {
				LOG("ExpectationWarning:\t \"%s\",\n", info->warning_expects[i].expr);
				LOG("\t\t \"%s\" \n\n", info->warning_expects[i].msg);
			} else {
				LOG("ExpectationWarning:\t \"%s\",\t\"%s\" \n\n", info->warning_expects[i].expr,
				    info->warning_expects[i].msg);
			}
				
		}
		else LOG("ExpectationWarning:\t \"%s\"\n\n", info->warning_expects[i].expr);
	}
}

