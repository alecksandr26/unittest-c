/*!
  @file unittest_recompile.h
  @brief his module provides functionality for managing the compilation and recompilation of test files.
  The module defines a C structure for a compiler context and two functions: "recompile" and "rerun".

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_RECOMPILE_INCLUDE
#define UNITTEST_RECOMPILE_INCLUDE
#define C UnitCompilerContex

/* For compiling the test files */
#define COMPILER	 "gcc"
#define COMPILER_PATH	 "/usr/bin/"
#define COMPILER_FLAGS	 "-ggdb -pedantic -Wall"
#define DATE_HASHED_FILE ".date_hashed.bin"
#define OBJ_DIR		 ".obj/"
#define TEST_DIR	 "./"
#define TEST_OUT	 "test"

#ifndef NDEBUG
#define LIB_UNITTEST "../lib/libunittest.a"
#else
#define LIB_UNITTEST "-lunittest"
#endif

typedef struct C C;
struct C {
	const char *compiler, *compiler_path, *compiler_flags;
};

/* unittest_recompile_without_tests: Re-compiles the source file into an executable
 * without including any test files. */
extern void unittest_recompile_without_tests(const C c, const char *file,
					     const char *outfile);

/* unittest_rerun_with_tests: Re-executes the test program with the test files already
 * loaded. */
extern void unittest_rerun_with_tests(const char *outfile);

/* unittest_recompile_with_tests: Re-compiles and links the source files including the
   tests files,
   Re-producing a new executable. */
extern void unittest_recompile_with_tests(const C c, const char *test_dir,
					  const char *obj_dir, const char *file,
					  const char *outfile);

#undef C
#endif
