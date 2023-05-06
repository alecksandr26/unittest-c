/*!
  @file unittest_suit.c
  @brief This is the implementation of the module of suits which contains the function that links the
  test cases from the suit to be runned.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/
#include "../include/unittest_suit.h"

#include "../include/unittest_tcase.h"
#define S Suit

/* link_suit_testcases: to link together the test cases contained within the suit
 * structure to run them */
void link_suit_testcases(S *suit)
{
	for (size_t i = 0; i < suit->amount; i++)
		link_tcase(suit->tcase[i]);
}
#undef S
