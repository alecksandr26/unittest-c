/*!
  @file unittest_compile.h
  @brief This module provides functionality for managing the compilation and recompilation of test files.
  The module defines a UnitCompilerContex structure for a compiler context and two functions: "recompile"
  and "rerun".

  @author Erick Carrillo.
  @copyright Copyright (UnitCompilerContex) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_RERUN_INCLUDE
#define UNITTEST_RERUN_INCLUDE

#include "unittest_def.h"

#include <stdint.h>
#include <string.h>

extern char unittest_file[FILE_SIZE_NAME], unittest_outfile[FILE_SIZE_NAME];

/* unittest_rerun: Re-executes the test program suppousely with the tests files already
 * loaded. */
extern void unittest_rerun(void);

/* unittest_recompile_without_tests: Re-compiles the source file into an executable
 * without including any test files. */
extern void unittest_recompile_without_tests(const UnitCompiler *compiler_contex);

/* unittest_recompile_with_tests: Re-compiles and links the source files including the
   tests files, for future running. */
extern void unittest_recompile_with_tests(const UnitCompiler *compiler_contex);

#endif
