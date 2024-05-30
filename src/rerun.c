/*!
  @file rerun.c
  @brief This module contains implementations for recompiling the main executable
  program with or without test files and for rerunning the program after recompilation.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License.
*/

#include "../include/unittest_command.h"
#include "../include/unittest_compile.h"
#include "../include/unittest_debug.h"
#include "../include/unittest_def.h"
#include "../include/unittest_dir.h"
#include "../include/unittest_tfile.h"
#include "../include/unittest_valgrind.h"

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>

/* unittest_rerun: Re-executes the test program suppousely with the tests files already
 * loaded. */
void unittest_rerun(void)
{
	UnitCommand command;

	unittest_init_command(&command);

	char executable[50];
	memset(executable, 0, sizeof(executable));
	strcpy(executable, "./");
	strcat(executable, unittest_outfile);

	if (unittest_run_valgrind) {
		unittest_attach_args(&command, VALGRIND);
		unittest_attach_args(&command, VALGRIND_FLAGS);
		strcpy(command.executable_command, VALGRIND_PATH);
		strcat(command.executable_command, VALGRIND);
	} else strcpy(command.executable_command, executable);

	unittest_attach_args(&command, executable);

	/* Catch the unittest_return code and set it in 1 */
	if (unittest_execute(&command) != 0) {
		extern int unittest_ret;
		unittest_ret = 1;
	}
}

/* unittest_recompile_without_tests: Re-compiles the source file into an executable
 * without including any test files. */
void unittest_recompile_without_tests(const UnitCompiler *compiler_contex)
{
	UnitCommand command;

	unittest_init_command(&command);

	strcpy(command.executable_command, compiler_contex->compiler_path);

	unittest_attach_args(&command, compiler_contex->compiler);
	unittest_attach_args(&command, compiler_contex->compiler_flags);
	unittest_attach_args(&command, unittest_file);

#ifndef NDEBUG
	unittest_attach_args(&command, "-L./lib");
#endif
	unittest_attach_args(&command, LIB_UNITTEST);
	unittest_attach_args(&command, LIB_EXCEPT);

	unittest_attach_args(&command, "-o");
	unittest_attach_args(&command, unittest_outfile);

	if (unittest_execute(&command) != 0)
		ABORT("Recompiling TestRunner %s -o %s\n", unittest_file,
		      unittest_outfile);
}

/* unittest_recompile_with_tests: Re-compiles and links the source files including the
   tests files, Re-producing a new executable. */
void unittest_recompile_with_tests(const UnitCompiler *compiler_contex)
{
	char   objs[MAX_AMOUNT_OF_TEST_FILES][FILE_SIZE_NAME];
	char  *objs_ptr[MAX_AMOUNT_OF_TEST_FILES];
	size_t n_objs = 0, objs_to_update = 0;

	unittest_create_obj_directory();
	memset(objs, 0, sizeof(objs));

	n_objs = 0;
	for (size_t i = 0; i < unittest_tfile_count; i++) {
		/* Catch the object file */
		strcat(objs[n_objs], unittest_objdir);
		strcat(objs[n_objs], unittest_tfiles[i].name);

		/* Change the last character test.c -> test.o */
		objs[n_objs][strlen(objs[n_objs]) - 1] = 'o';

		/* Check if there were changes, or if it even exist that file */
		if (unittest_tfile_needs_update(&unittest_tfiles[i])
		    || access(objs[n_objs], F_OK) == -1) {
			char source[FILE_SIZE_NAME];
			memset(source, 0, FILE_SIZE_NAME);
			strcat(source, unittest_testdir);
			strcat(source, unittest_tfiles[i].name);

			LOG("[COMPILING]:\t%s -o %s\n", source, objs[n_objs]);
			if (compile_obj(compiler_contex, source, objs[n_objs]) != 0) {
#ifndef NDEBUG /* For debugin the framework */
				LOG("[TESTING]: Compiling error catched, exiting with "
				    "success...\n");
				exit(EXIT_SUCCESS);
#else
				ABORT("Error compiling object %s -o %s\n", source,
				      objs[n_objs]);
#endif
			}
			objs_to_update++;
		}
		objs_ptr[n_objs] = objs[n_objs];
		n_objs++;
	}

	/* Link the compiled testfiles */
	if (objs_to_update > 0)
		LOG("[LINKING]:\t%s %s %s -o %s\n", unittest_file, objs[0],
		    (objs_to_update > 1) ? ", ..." : "", unittest_outfile);

	if (link_objs(compiler_contex, unittest_file, (const char **) objs_ptr, n_objs,
		      unittest_outfile) != 0)
		ABORT("Error linking all the testfiles\n");
}
