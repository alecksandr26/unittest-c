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

#define MAX_AMOUNT_OF_TESTS_IN_TESTCASES 128
#define MAX_AMOUNT_OF_TESTCASES 1024
#define MAX_AMOUNT_OF_TESTS_INFO_FAILD 131072 /* 1024 * 128 */
#define MAX_AMOUNT_OF_TESTCASES_IN_SUITS 128
#define MAX_AMOUNT_OF_SUITS 1024
#define MAX_AMOUNT_OF_TEST_FILES	     128
#define MAX_AMOUNT_OF_SUITS_IN_FILES 128
#define TEST_FILE_NAME_SIZE 100
#define COMPILER	 "cc"
#define COMPILER_PATH	 "/usr/bin/"
#define COMPILER_FLAGS	 "-ggdb -pedantic -Wall"
#define LIB_UNITTEST	 "-lunittest"
#define VALGRIND	 "valgrind"
#define VALGRIND_PATH	 "/usr/bin/"
#define VALGRIND_FLAGS	 "--quiet"
#define DATE_HASHED_FILE ".date_hashed.bin"
#define TEST_OBJ_DIR	 ".obj/"
#define TEST_DIR	 "./"
#define TEST_OUT	 "testrunner"
#define MAX_AMOUNT_OF_ARGUMENTS 128
#define COMMAND_SIZE 1024
#define BINARY_COMMAND_SIZE 128
#define LINKING_FLAGS_SIZE 1024
#define COMPILING_FLAGS_SIZE 1024
#define FLAGS_BUFF_SIZE 1024
#define COMPILED_FAILD 1
#define COMPILED_SUCCESS 0
#define UNITTEST_STD_OUT 1
#define UNITTEST_STD_ERR 2
#define FILE_SIZE_NAME 256
#define ERROR_INFO_MSG_SIZE 256


#define TEST_CASE_OUTPUT_BUFF_SIZE	 1024


#endif




