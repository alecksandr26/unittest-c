/*!
  @file suit.c
  @brief This is the source code implementation for the 'unittest_suit.h' component.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_suit.h"

#include <assert.h>

/* unittest_link_suit_tcase: to link together the test cases contained within the suit
 * structure to run them */
void unittest_link_suit_tcase(UnitSuit *suit)
{
	assert(suit != NULL && "Can't receive a null suit ptr");

	for (size_t i = 0; i < suit->amount; i++)
		unittest_link_tcase(suit->tcase[i]);
}
