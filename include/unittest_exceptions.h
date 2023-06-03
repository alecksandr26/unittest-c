/*!
  @file unittest_exceptions.h
  @brief Contains all the exception messages that could occur during the execution of the unittesting library.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_EXCEPTIONS_INCLUDED
#define UNITTEST_EXCEPTIONS_INCLUDED

/* Uses another moulde that I wrote :)
   link: https://github.com/alecksandr26/c-exceptions
 */
#include <tc.h>

extern Except UnittestNotEnoughMemory;
extern Except UnittestErrorOpeningFile;
extern Except UnittestErrorCreatingFile;
extern Except UnittestErrorReadingFile;
extern Except UnittestErrorCreatingDir;
extern Except UnittestErrorTestBaseDoesntExist;
extern Except UnittestErrorWrittingFile;
extern Except UnittestNoneTests;

#endif
