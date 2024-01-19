/*!
  @file unittest_compile.h
  @brief This module provides functionality for compiling the test files and linking the whole testfiles,
  with flags.

  @author Erick Carrillo.
  @copyright Copyright (UnitCompilerContex) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_COMPILE_INCLUDE
#define UNITTEST_COMPILE_INCLUDE

#include <stddef.h>
#include <string.h>

#include "unittest_def.h"
#include "unittest_tfile.h"

typedef struct  {
	const char *compiler, *compiler_path, *compiler_flags;
} UnitCompiler;

/* Attach any extra flags needed for the linking compilation process of the tests */
#define ATTACH_EXTRA_LINKING_FLAGS(FLAGS) unittest_catch_extra_linking_flags(FLAGS)

/* Attach any extra flags needed for the compilation of each test */
#define ATTACH_EXTRA_COMPILE_FLAGS(FLAGS) unittest_catch_extra_compile_flags(FLAGS)

/* An external pointer that points to external or static libraries */
extern void unittest_catch_extra_linking_flags(const char *flags);
extern void unittest_catch_extra_compile_flags(const char *flags);

/* compile_obj: To compile some obj file, returns the return status of the compilation. */
extern int compile_obj(const UnitCompiler *compiler_contex, const char *source, const char *obj);

/* link_objs: To link the entire objects file into a testrunner, returns the return status of the linkage
   of the objects. */
extern int link_objs(const UnitCompiler *compiler_contex, const char *file, const char **objs,
		     size_t amount_objs, const char *out);

#endif









