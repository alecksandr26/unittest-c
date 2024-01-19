/*!
  @file unittest.h
  @brief This is the interface for a C unit testing framework. It includes macros to define and run
  test cases and test suites, as well as functions to check the existence of test files and recompile
  the program with test files. The framework also supports catching exceptions thrown by the test cases.
  The macros and functions are defined in different header files included in this interface.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_INCLUDE
#define UNITTEST_INCLUDE

#include "unittest_compile.h"
#include "unittest_debug.h"
#include "unittest_exceptions.h"
#include "unittest_suit.h"
#include "unittest_tcase.h"
#include "unittest_tfile.h"

#include <stdlib.h>
#include <unistd.h>

/* unittest_fetch_filesname: This functions gets the paths for the needed files */
extern void unittest_fetch_filesname(const char *file, const char *outfile,
				     const char *testdir, const char *objdir,
				     const char *hashed_file);

/* unittest_check_testdir_exist: This function checks whether the test directory exists or
 * not. */
extern void unittest_check_testdir_exist(void);

/* unittest_run_tests: Executes the test cases that were linked using the provided macros.
 */
extern int unittest_run_tests(void);

/* To muting the output from the tests */
extern int unittest_mute_mode, unittest_ret, unittest_running_tests;

#ifdef UNITTEST_RECOMPILE
#define RUN(...)                                                                  \
	if (UNITTEST_RECOMPILE) {					\
		UnitCompiler compiler_contex = {.compiler	= COMPILER, \
					.compiler_path	= COMPILER_PATH COMPILER, \
					.compiler_flags = COMPILER_FLAGS};        \
		unittest_check_testdir_exist();                                   \
		unittest_get_prev_dates();				\
		unittest_recompile_with_tests(&compiler_contex);	\
		unittest_put_new_dates();                                         \
		unittest_rerun_with_tests();				\
		unittest_recompile_without_tests(c);                              \
	} else {                                                                  \
		unittest_running_tests = 1;                                       \
		__VA_OPT__(CATCH(__VA_ARGS__));                                   \
		unittest_run_tests();					\
	}
#else
#undef INCLUDE_SUIT
#define INCLUDE_SUIT(filename, ...)  \
	extern UnitSuit __VA_ARGS__; \
	CATCH(__VA_ARGS__)
#undef INCLUDE_TESTCASE
#define INCLUDE_TESTCASE(filename, ...)	 \
	extern UnitTestCase __VA_ARGS__; \
	CATCH(__VA_ARGS__)
#define RUN(...)                        \
	unittest_running_tests = 1;     \
	__VA_OPT__(CATCH(__VA_ARGS__)); \
	unittest_run_tests()
#endif

#define CATCH_GENERIC(X)                           \
	_Generic((X),                              \
		UnitTestCase: unittest_link_tcase, \
		UnitSuit: unittest_link_suit_tcase)(&X)

/* Simple recursive macros */
#define CATCH(first, ...)   CATCH_GENERIC(first) __VA_OPT__(; CATCH1(__VA_ARGS__))
#define CATCH1(first, ...)  CATCH_GENERIC(first) __VA_OPT__(; CATCH2(__VA_ARGS__))
#define CATCH2(first, ...)  CATCH_GENERIC(first) __VA_OPT__(; CATCH3(__VA_ARGS__))
#define CATCH3(first, ...)  CATCH_GENERIC(first) __VA_OPT__(; CATCH4(__VA_ARGS__))
#define CATCH4(first, ...)  CATCH_GENERIC(first) __VA_OPT__(; CATCH5(__VA_ARGS__))
#define CATCH5(first, ...)  CATCH_GENERIC(first) __VA_OPT__(; CATCH6(__VA_ARGS__))
#define CATCH6(first, ...)  CATCH_GENERIC(first) __VA_OPT__(; CATCH7(__VA_ARGS__))
#define CATCH7(first, ...)  CATCH_GENERIC(first) __VA_OPT__(; CATCH8(__VA_ARGS__))
#define CATCH8(first, ...)  CATCH_GENERIC(first) __VA_OPT__(; CATCH9(__VA_ARGS__))
#define CATCH9(first, ...)  CATCH_GENERIC(first) __VA_OPT__(; CATCH10(__VA_ARGS__))
#define CATCH10(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH11(__VA_ARGS__))
#define CATCH11(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH12(__VA_ARGS__))
#define CATCH12(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH13(__VA_ARGS__))
#define CATCH13(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH14(__VA_ARGS__))
#define CATCH14(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH15(__VA_ARGS__))
#define CATCH15(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH16(__VA_ARGS__))
#define CATCH16(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH17(__VA_ARGS__))
#define CATCH17(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH18(__VA_ARGS__))
#define CATCH18(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH19(__VA_ARGS__))
#define CATCH19(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH20(__VA_ARGS__))
#define CATCH20(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH21(__VA_ARGS__))
#define CATCH21(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH22(__VA_ARGS__))
#define CATCH22(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH23(__VA_ARGS__))
#define CATCH23(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH24(__VA_ARGS__))
#define CATCH24(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH25(__VA_ARGS__))
#define CATCH25(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH26(__VA_ARGS__))
#define CATCH26(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH27(__VA_ARGS__))
#define CATCH27(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH28(__VA_ARGS__))
#define CATCH28(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH29(__VA_ARGS__))
#define CATCH29(first, ...) CATCH_GENERIC(first) __VA_OPT__(; CATCH30(__VA_ARGS__))
#define CATCH30(...)

#endif
