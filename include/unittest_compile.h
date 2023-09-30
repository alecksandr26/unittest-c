/*!
  @file unittest_compile.h
  @brief his module provides functionality for managing the compilation and recompilation of test files.
  The module defines a C structure for a compiler context and two functions: "recompile" and "rerun".

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_COMPILE_INCLUDE
#define UNITTEST_COMPILE_INCLUDE
#define C UnitCompilerContex

#include <stdint.h>
#include <string.h>

/* For compiling the test files */
#define VALGRIND	 "valgrind"
#define VALGRIND_PATH	 "/usr/bin/"
#define VALGRIND_FLAGS	 "--quiet"
#define COMPILER	 "cc"
#define COMPILER_PATH	 "/usr/bin/"
#define COMPILER_FLAGS	 "-ggdb -pedantic -Wall"
#define DATE_HASHED_FILE ".date_hashed.bin"
#define TEST_OBJ_DIR	 ".obj/"
#define TEST_DIR	 "./"
#define TEST_OUT	 "test"
#define LIB_UNITTEST	 "-lunittest"

typedef struct C C;
struct C {
	const char *compiler, *compiler_path, *compiler_flags;
};

/* An external pointer that points to external or static libraries */
extern void    unittest_attach_extra_linking_flags(const char *flags);
extern void    unittest_attach_extra_compile_flags(const char *flags);
extern uint8_t unittest_run_valgrind;

/* ACTIVE_VALGRIND: To active valgrind into the execution */
#define ACTIVE_VALGRIND() unittest_run_valgrind = 1

/* Attach any extra flags needed for the linking compilation process of the tests */
#define ATTACH_EXTRA_LINKING_FLAGS(FLAGS) unittest_attach_extra_linking_flags(FLAGS)

/* Attach any extra flags needed for the compilation of each test */
#define ATTACH_EXTRA_COMPILE_FLAGS(FLAGS) unittest_attach_extra_compile_flags(FLAGS)

/* unittest_recompile_without_tests: Re-compiles the source file into an executable
 * without including any test files. */
extern void unittest_recompile_without_tests(const C c);

/* unittest_rerun_with_tests: Re-executes the test program with the test files already
 * loaded. */
extern void unittest_rerun_with_tests(void);

/* unittest_recompile_with_tests: Re-compiles and links the source files including the
   tests files,
   Re-producing a new executable. */
extern void unittest_recompile_with_tests(const C c);

#undef C
#endif
