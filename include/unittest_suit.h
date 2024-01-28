/*!
  @file unittest_suit.h
  @brief This module provides functionality to create collections or suites of test cases for unit testing.
  It defines a struct UnitSuit that contains an array of test cases, a count of the number of test cases, and a
  name for the suite. It also provides macros to create a new suite and to link the test cases in the suite.
  The unittest_link_suit_tcase() function is used to link the test cases structures together for the running
  process.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_SUIT_INCLUDED
#define UNITTEST_SUIT_INCLUDED

#include "unittest_def.h"
#include "unittest_tcase.h"

/* This structure defines a test suite, consisting of an array of test cases, the number
   of test
   cases, and the name of the suite. */
typedef struct {
	UnitTestCase *tcase[MAX_AMOUNT_OF_TESTCASES_IN_SUITS];
	size_t	      amount;
	const char   *name;
} UnitSuit;

/* SUIT: creates a new test suite with a given name and a list of test cases.  */
#define SUIT(SUIT_NAME, ...)                                                             \
	UnitSuit SUIT_NAME = {.tcase  = {ADDR(__VA_ARGS__)},                             \
			      .amount = sizeof((UnitTestCase *[]) {ADDR(__VA_ARGS__)}) / \
					sizeof(UnitTestCase *),                          \
			      .name = #SUIT_NAME}

/* unittest_link_suit_tcase: to link together the test cases contained within the suit
 * structure to run them */
extern void unittest_link_suit_tcase(UnitSuit *suit);

#define AMPR(...) __VA_OPT__(&) __VA_ARGS__

/* TODO: Create more recrusive macros to fill the buffer from a suit  */
#define ADDR(var, ...)	 AMPR(var) __VA_OPT__(, ) ADDR1(__VA_ARGS__)
#define ADDR1(var, ...)	 AMPR(var) __VA_OPT__(, ) ADDR2(__VA_ARGS__)
#define ADDR2(var, ...)	 AMPR(var) __VA_OPT__(, ) ADDR3(__VA_ARGS__)
#define ADDR3(var, ...)	 AMPR(var) __VA_OPT__(, ) ADDR4(__VA_ARGS__)
#define ADDR4(var, ...)	 AMPR(var) __VA_OPT__(, ) ADDR5(__VA_ARGS__)
#define ADDR5(var, ...)	 AMPR(var) __VA_OPT__(, ) ADDR6(__VA_ARGS__)
#define ADDR6(var, ...)	 AMPR(var) __VA_OPT__(, ) ADDR7(__VA_ARGS__)
#define ADDR7(var, ...)	 AMPR(var) __VA_OPT__(, ) ADDR8(__VA_ARGS__)
#define ADDR8(var, ...)	 AMPR(var) __VA_OPT__(, ) ADDR9(__VA_ARGS__)
#define ADDR9(var, ...)	 AMPR(var) __VA_OPT__(, ) ADDR10(__VA_ARGS__)
#define ADDR10(var, ...) AMPR(var) __VA_OPT__(, ) ADDR11(__VA_ARGS__)
#define ADDR11(var, ...) AMPR(var) __VA_OPT__(, ) ADDR12(__VA_ARGS__)
#define ADDR12(var, ...) AMPR(var) __VA_OPT__(, ) ADDR13(__VA_ARGS__)
#define ADDR13(var, ...) AMPR(var) __VA_OPT__(, ) ADDR14(__VA_ARGS__)
#define ADDR14(var, ...) AMPR(var) __VA_OPT__(, ) ADDR15(__VA_ARGS__)
#define ADDR15(var, ...) AMPR(var) __VA_OPT__(, ) ADDR16(__VA_ARGS__)
#define ADDR16(var, ...) AMPR(var) __VA_OPT__(, ) ADDR17(__VA_ARGS__)
#define ADDR17(var, ...) AMPR(var) __VA_OPT__(, ) ADDR18(__VA_ARGS__)
#define ADDR18(var, ...) AMPR(var) __VA_OPT__(, ) ADDR19(__VA_ARGS__)
#define ADDR19(var, ...) AMPR(var) __VA_OPT__(, ) ADDR20(__VA_ARGS__)
#define ADDR20(var, ...) AMPR(var) __VA_OPT__(, ) ADDR21(__VA_ARGS__)
#define ADDR21(var, ...) AMPR(var) __VA_OPT__(, ) ADDR22(__VA_ARGS__)
#define ADDR22(var, ...) AMPR(var) __VA_OPT__(, ) ADDR23(__VA_ARGS__)
#define ADDR23(var, ...) AMPR(var) __VA_OPT__(, ) ADDR24(__VA_ARGS__)
#define ADDR24(var, ...) AMPR(var) __VA_OPT__(, ) ADDR25(__VA_ARGS__)
#define ADDR25(var, ...) AMPR(var) __VA_OPT__(, ) ADDR26(__VA_ARGS__)
#define ADDR26(var, ...) AMPR(var) __VA_OPT__(, ) ADDR27(__VA_ARGS__)
#define ADDR27(var, ...) AMPR(var) __VA_OPT__(, ) ADDR28(__VA_ARGS__)
#define ADDR28(var, ...) AMPR(var) __VA_OPT__(, ) ADDR29(__VA_ARGS__)
#define ADDR29(var, ...) AMPR(var) __VA_OPT__(, ) ADDR30(__VA_ARGS__)
#define ADDR30(var, ...) AMPR(var) __VA_OPT__(, ) ADDR31(__VA_ARGS__)
#define ADDR31(var, ...) AMPR(var) __VA_OPT__(, ) ADDR32(__VA_ARGS__)
#define ADDR32(var, ...) AMPR(var) __VA_OPT__(, ) ADDR33(__VA_ARGS__)
#define ADDR33(var, ...) AMPR(var) __VA_OPT__(, ) ADDR34(__VA_ARGS__)
#define ADDR34(...)

#endif
