/*!
  @file unittest_valgrind.h
  @brief This module provides functionality for managing the valgrind addition for the testcases.

  @author Erick Carrillo.
  @copyright Copyright (UnitCompilerContex) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_VALGRIND_INCLUDED
#define UNITTEST_VALGRIND_INCLUDED

#include "unittest_def.h"

#include <stdbool.h>

extern bool unittest_run_valgrind;

/* ACTIVE_VALGRIND: To active valgrind into the execution */
#define ACTIVE_VALGRIND(BOOL) unittest_run_valgrind = BOOL

#endif
