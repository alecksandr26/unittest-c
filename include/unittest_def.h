/*!
  @file unittest_def.h
  @brief This is the header which contain all the default constants, like the max amount of testcases,
  the max amount of tests in testcases, etc.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_DEF_INCLUDE
#define UNITTEST_DEF_INCLUDE

#define MAX_AMOUNT_OF_TESTS_IN_TESTCASES	    128
#define MAX_AMOUNT_OF_TESTCASES			    1024
#define MAX_AMOUNT_OF_INFO_FAILES		    1024
#define MAX_AMOUNT_OF_FAILED_ASSERTIONS_IN_TESTCASE 128
#define MAX_AMOUNT_OF_ASSERTS_IN_TESTS		    128
#define MAX_AMOUNT_OF_MSGS_IN_TESTS		    128
#define MAX_AMOUNT_OF_TESTCASES_IN_SUITS	    128
#define MAX_AMOUNT_OF_SUITS			    1024
#define MAX_AMOUNT_OF_TEST_FILES		    128
#define MAX_AMOUNT_OF_SUITS_IN_FILES		    128
#define MAX_AMOUNT_OF_ARGUMENTS			    128

#ifndef COMPILER
#define COMPILER "cc"
#endif

#ifndef COMPILER_PATH
#define COMPILER_PATH "/usr/bin/"
#endif

#ifndef COMPILER_FLAGS
#define COMPILER_FLAGS "-ggdb -pedantic -Wall"
#endif

#define LIB_UNITTEST  "-lunittest"

#define VALGRIND      "valgrind"
#define VALGRIND_PATH "/usr/bin/"
#define VALGRIND_FLAGS "--quiet --leak-check=full --show-leak-kinds=all --track-origins=yes"

#ifndef DATE_HASHED_FILE
#define DATE_HASHED_FILE ".date_hashed.bin"
#endif

#ifndef TEST_OBJ_DIR
#define TEST_OBJ_DIR ".obj/"
#endif

#ifndef TEST_DIR
#define TEST_DIR "./"
#endif

#ifndef TEST_OUT
#define TEST_OUT "testrunner"
#endif

#define COMMAND_SIZE	     1024
#define BINARY_COMMAND_SIZE  128
#define LINKING_FLAGS_SIZE   1024
#define COMPILING_FLAGS_SIZE 1024
#define FLAGS_BUFF_SIZE	     1024
#define INFO_MSG_SIZE  256
#define EXPR_LENGHT_SIZE     256
#define UNITTEST_STR_SIZE    1024

#define DIR_SIZE_NAME	     256
#define FILE_SIZE_NAME	     256

#define COMPILED_FAILD	     1
#define COMPILED_SUCCESS     0
#define UNITTEST_STD_OUT     1
#define UNITTEST_STD_ERR     2

#define DIV_LINE_STR                                                                  \
	"---------------------------------------------------------------------------" \
	"----------------\n"

#define DIV_DOUBLE_LINE_STR                                                           \
	"===========================================================================" \
	"================\n"

#endif
