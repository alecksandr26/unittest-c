/*!
  @file infofail.c
  @brief The source code for the unittest_info.h component.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_assert.h"
#include "../include/unittest_debug.h"
#include "../include/unittest_def.h"
#include "../include/unittest_info.h"

#include <assert.h>
#include <stdbool.h>

_Static_assert(MAX_AMOUNT_OF_TESTS_IN_TESTCASES == 128, "This should 128 testscases");
_Static_assert(MAX_AMOUNT_OF_TESTCASES == 1024, "This should 1024 testscases");
_Static_assert(MAX_AMOUNT_OF_INFO_FAILES == 1024, "This initialy should be 1024 * 128");

UnitTestInfo *unittest_infotestcases[MAX_AMOUNT_OF_INFO_FAILES];


/* unitteest_check_if_test_failed_or_warned: Returns true if the a test got a warn or a fail. */
static bool unittest_check_if_test_failed_or_warned(const UnitTestInfo *info, const char *test)
{
	assert(info != NULL && test != NULL &&  "Can't be null");

	bool res = false;
	for (size_t i = 0; i < info->number_failed_asserts; i++)
		if (strcmp(test, info->failed_asserts[i].test) == 0)
			res = true;
	for (size_t i = 0; i < info->number_warning_expects; i++)
		if (strcmp(test, info->warning_expects[i].test) == 0)
			res = true;
	return res;
}

/* unittest_print_info_testcase: This function prints the information for a failed test,
   including the expression, message, test name, testcase name and filename. */
void unittest_print_info_testcase(const UnitTestInfo *info)
{
	assert(info != NULL && "Can't be null");
	
	/* Prints the asserts */
	for (size_t i = 0; i < info->number_failed_asserts; i++) {
		LOG(DIV_DOUBLE_LINE_STR);

		LOG("FAIL:\t\t%s\t\t(%s.%s)\n", info->failed_asserts[i].test,
		    info->unitcase, info->failed_asserts[i].test);
		LOG(DIV_LINE_STR);
		LOG("Traceback...\n");
		LOG("\tFile \"%s\", line %i, in %s\n", info->file,
		    info->failed_asserts[i].line, info->failed_asserts[i].test);
		if (info->failed_asserts[i].msg != NULL) {
			if (strlen(DIV_LINE_STR) <
			    strlen(info->failed_asserts[i].expr) + 18) {
				LOG("AssertionError:\t \"%s\",\n",
				    info->failed_asserts[i].expr);
				LOG("\t\t \"%s\" \n\n", info->failed_asserts[i].msg);
			} else {
				LOG("AssertionError:\t \"%s\",\t \"%s\" \n\n",
				    info->failed_asserts[i].expr,
				    info->failed_asserts[i].msg);
			}

		} else LOG("AssertionError:\t \"%s\"\n\n", info->failed_asserts[i].expr);
	}

	/* Prints the expects */
	for (size_t i = 0; i < info->number_warning_expects; i++) {
		LOG(DIV_DOUBLE_LINE_STR);

		LOG("WARN:\t\t%s\t\t(%s.%s)\n", info->warning_expects[i].test,
		    info->unitcase, info->warning_expects[i].test);
		LOG(DIV_LINE_STR);
		LOG("Traceback...\n");
		LOG("\tFile \"%s\", line %i, in %s\n", info->file,
		    info->warning_expects[i].line, info->warning_expects[i].test);
		if (info->warning_expects[i].msg != NULL) {
			if (strlen(DIV_LINE_STR) <
			    strlen(info->warning_expects[i].expr) + 18) {
				LOG("ExpectationWarning:\t \"%s\",\n",
				    info->warning_expects[i].expr);
				LOG("\t\t \"%s\" \n\n", info->warning_expects[i].msg);
			} else {
				LOG("ExpectationWarning:\t \"%s\",\t\"%s\" \n\n",
				    info->warning_expects[i].expr,
				    info->warning_expects[i].msg);
			}

		} else
			LOG("ExpectationWarning:\t \"%s\"\n\n",
			    info->warning_expects[i].expr);
	}


	/* Prints Info messages */
	for (size_t i = 0; i < info->number_info_msgs; i++) {
		if (!unittest_check_if_test_failed_or_warned(info, info->info_msgs[i].test))
			continue;
		
		LOG(DIV_DOUBLE_LINE_STR);
		LOG("INFO:\t\t%s\t\t(%s.%s)\n", info->info_msgs[i].test,
		    info->unitcase, info->info_msgs[i].test);
		LOG(DIV_LINE_STR);
		LOG("\tFile \"%s\", line %i, in %s\n", info->file,
		    info->info_msgs[i].line, info->info_msgs[i].test);
		LOG("InformationMessage: \"%s\"\n\n", info->info_msgs[i].msg);
	}
}
