/*!
  @file unittest.h
  @brief A set of macros to create new testcases or thats the idea.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_INCLUDE
#define UNITTEST_INCLUDE

#include <assert.h>
#include <except.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


#define TF TestCaseFrame
#define TC TestCase
#define S  Suit
#define C  CompilerContex
#define F TestInfoFailed

/* Contants */
#define MAX_AMOUNT_OF_TESTS_IN_SUITS 1024
#define MAX_AMOUNT_OF_SUITS_IN_FILES 100
#define MAX_AMOUNT_OF_FILES	     100
#define MAX_AMOUNT_OF_TESTS 100

/* For recompiling the suits */
#define COMPILER	 "gcc"
#define COMPILER_PATH	 "/usr/bin/"
#define COMPILER_FLAGS	 "-ggdb -pedantic -Wall"
#define DATE_HASHED_FILE ".date_hashed.bin"
#define OBJ_DIR		 ".obj/"
#define TEST_DIR	 "./"
#define TEST_OUT	 "test"

typedef struct F F;
struct F {
	const char *expr, *msg;
	int line;
};

/* Compile contex */
typedef struct C C;
struct C {
	const char *compiler, *compiler_path, *compiler_flags;
};

/* The structure to keep track the tests */
typedef struct TF TF;
struct TF {
	volatile int state;
	const char  *current_test;
	int	     counter;
	char status;

	JmpBuf buf;
};

/* The structure to keep track the testscases */
typedef struct TC TC;
struct TC {
	const char *file, *name;
	size_t	    amount, amount_failed;
	TC	   *next;

	/* Catch the test function */
	void (*test)(TC *);
	F failed_info[MAX_AMOUNT_OF_TESTS];
};

#include "unittest_assert.h"

/* To keep track the testcases */
typedef struct S S;
struct S {
	TC	   *tcase[MAX_AMOUNT_OF_TESTS_IN_SUITS];
	size_t	    amount;
	const char *name;
};

/* Import the procedures */
extern void   run_tests(void);
extern void   attach_file(const char *test_dir, const char *filename);
extern void   recompile(const CompilerContex c, const char *test_dir,
			const char *hashed_file_name, const char *obj_dir, const char *file,
			const char *outfile);
extern void   link_tcase(TC *tcase);
extern void   link_suit(S *suit);
extern void   rerun(const CompilerContex c, const char *file, const char *outfile);
extern TC    *head_tc;
extern Except UnittestNotEnoughMemory, UnittestErrorOpeningFile,
	UnittestErrorCreatingFile, UnittestErrorReadingFile, UnittestErrorCreatingDir,
	UnittestErrorTestBaseDoesntExist, UnittestErrorWrittingFile;

/* To create a new testcase */
#define TestCase(TEST_CASE_NAME)					\
	void	 tcase_##TEST_CASE_NAME(TestCase *tcase);		\
	TestCase TEST_CASE_NAME = {					\
		.file   = __FILE__,					\
		.name   = #TEST_CASE_NAME,				\
		.amount = 0,						\
		.amount_failed = 0,					\
		.next = NULL,						\
		.test   = &tcase_##TEST_CASE_NAME,			\
		.failed_info = {{0}}					\
	};								\
	void	 tcase_##TEST_CASE_NAME(TestCase *tcase)		\
	{								\
	assert(tcase != NULL && "Can't be null amount tests");		\
	TestCaseFrame tframe;						\
	tframe.state   = stackjmp(&tframe.buf);				\
	tframe.counter = 0;						\
	tframe.status = '.';						\
	do

/* To run an specific test */
#define Test(TEST_NAME)                         \
	tframe.current_test = #TEST_NAME;       \
	/* Count all the tests */               \
	if (tframe.state == 0) tcase->amount++; \
	if (tframe.state == ++tframe.counter)

#define EndTestCase							\
	while (0)							\
		;							\
	assert(tcase->amount > 0					\
	       && "The testcase should have atleast one test");		\
	if (tframe.state > 0)						\
		putchar(tframe.status);					\
	if (tframe.state < (int) tcase->amount) 			\
		jmpback(&tframe.buf, tframe.state + 1);			\
									\
	}

/* Some recursive macros */
#define AMPR(...)	__VA_OPT__(&) __VA_ARGS__
#define ADDR(var, ...)	AMPR(var) __VA_OPT__(, ) ADDR1(__VA_ARGS__)
#define ADDR1(var, ...) AMPR(var) __VA_OPT__(, ) ADDR2(__VA_ARGS__)
#define ADDR2(var, ...) AMPR(var) __VA_OPT__(, ) ADDR3(__VA_ARGS__)
#define ADDR3(var, ...) AMPR(var) __VA_OPT__(, ) ADDR4(__VA_ARGS__)
#define ADDR4(var, ...) AMPR(var) __VA_OPT__(, ) ADDR5(__VA_ARGS__)
#define ADDR5(var, ...) AMPR(var) __VA_OPT__(, ) ADDR6(__VA_ARGS__)
#define ADDR6(var, ...) AMPR(var) __VA_OPT__(, ) ADDR7(__VA_ARGS__)
#define ADDR7(var, ...) AMPR(var) __VA_OPT__(, ) ADDR8(__VA_ARGS__)
#define ADDR8(var, ...) AMPR(var) __VA_OPT__(, ) ADDR9(__VA_ARGS__)
#define ADDR9(var, ...) AMPR(var) __VA_OPT__(, ) ADDR10(__VA_ARGS__)
#define ADDR10(...)

/* To create a new suit */
#define NEW_SUIT(SUIT_NAME, ...)                                                 \
	Suit SUIT_NAME = {.tcase  = {ADDR(__VA_ARGS__)},                         \
			  .amount = sizeof((TestCase *[]) {ADDR(__VA_ARGS__)}) / \
				    sizeof(TestCase *),                          \
			  .name = #SUIT_NAME}

/* CATCH_SUIT: To append the testcases from a suit */
#define CATCH_GENERIC(X)    _Generic((X), TestCase : link_tcase, Suit : link_suit)(&X)
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
#define CATCH11(...)

#ifndef UNITTEST_RECOMPILE
#define UNITTEST_RECOMPILE 0
#define INCLUDE_SUIT(filename, ...)      \
	attach_file(TEST_DIR, filename); \
	if (!UNITTEST_RECOMPILE) {       \
		extern Suit __VA_ARGS__; \
		CATCH(__VA_ARGS__);      \
	}
#define INCLUDE_TEST_CASE(filename, ...)     \
	attach_file(TEST_DIR, filename);     \
	if (!UNITTEST_RECOMPILE) {           \
		extern TestCase __VA_ARGS__; \
		CATCH(__VA_ARGS__);          \
	}
#define RUN(...)                                                                       \
	if (UNITTEST_RECOMPILE) {                                                      \
		CompilerContex c = {.compiler	    = COMPILER,                        \
				    .compiler_path  = COMPILER_PATH COMPILER,          \
				    .compiler_flags = COMPILER_FLAGS};                 \
		recompile(c, TEST_DIR, DATE_HASHED_FILE, OBJ_DIR, __FILE__, TEST_OUT); \
		rerun(c, __FILE__, TEST_OUT);                                          \
		return 0;                                                              \
	}                                                                              \
	__VA_OPT__(CATCH(__VA_ARGS__));                                                \
	run_tests();                                                                   \
	head_tc = NULL
#else
#define INCLUDE_SUIT(filename, ...)      \
	attach_file(TEST_DIR, filename); \
	extern Suit __VA_ARGS__;         \
	CATCH(__VA_ARGS__)
#define INCLUDE_TEST_CASE(filename, ...) \
	attach_file(TEST_DIR, filename); \
	extern TestCase __VA_ARGS__;     \
	CATCH(__VA_ARGS__)
#define RUN(...)                        \
	__VA_OPT__(CATCH(__VA_ARGS__)); \
	run_tests();                    \
	head_tc = NULL
#endif

#undef TF
#undef TC
#undef S
#undef C
#undef F 
#endif
