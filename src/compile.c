/*!
  @file compile.c
  @brief This is the souce code for the implementation of 'unittest_compile.h'.

  @author Erick Carrillo.
  @copyright Copyright (UnitCompilerContex) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_command.h"
#include "../include/unittest_compile.h"
#include "../include/unittest_def.h"

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <except.h>
#include <unistd.h>
#include <wait.h>

Except_T UnittestEmptyFlags = INIT_EXCEPT_T("Error empty flags passed");

char unittest_compile_extra_args_buff[COMPILING_FLAGS_SIZE];
char unittest_link_extra_args_buff[LINKING_FLAGS_SIZE];
bool unittest_compile_extra_args = false;
bool unittest_link_extra_args	 = false;

/* An external pointer that points to external or static libraries */
void unittest_catch_extra_linking_flags(const char *flags)
{
	size_t n = strlen(flags);

	if (n == 0) RAISE(UnittestEmptyFlags);

	memset(unittest_link_extra_args_buff, 0, n);
	strcpy(unittest_link_extra_args_buff, flags);
	unittest_link_extra_args = true;
}

void unittest_catch_extra_compile_flags(const char *flags)
{
	size_t n = strlen(flags);

	if (n == 0) RAISE(UnittestEmptyFlags);

	memset(unittest_compile_extra_args_buff, 0, n);
	strcpy(unittest_compile_extra_args_buff, flags);
	unittest_compile_extra_args = true;
}

/* compile_obj: To compile some obj file, returns the return status of the compilation. */
int compile_obj(const UnitCompiler *compiler_contex, const char *source, const char *obj)
{
	assert(compiler_contex != NULL && "Can't be null");
	assert(source != NULL && "Can't be null");
	assert(obj != NULL && "Can't be null");

	UnitCommand command;
	unittest_init_command(&command);
	strcpy(command.executable_command, compiler_contex->compiler_path);

	unittest_attach_args(&command, compiler_contex->compiler);
	unittest_attach_args(&command, compiler_contex->compiler_flags);
	unittest_attach_args(&command, "-c");
	unittest_attach_args(&command, source);
	unittest_attach_args(&command, "-o");
	unittest_attach_args(&command, obj);

	if (unittest_compile_extra_args)
		unittest_attach_args(&command, unittest_compile_extra_args_buff);
	return unittest_execute(&command);
}

/* link_objs: To link the entire objects file into a testrunner, returns the return status
   of the linkage
   of the objects. */
int link_objs(const UnitCompiler *compiler_contex, const char *file, const char **objs,
	      size_t amount_objs, const char *out)
{
	assert(compiler_contex != NULL && "Can't be null");
	assert(objs != NULL && "Can't be null");
	assert(amount_objs > 0 && "Can't link zero objs");
	assert(out != NULL && "Can't be null");

	UnitCommand command;
	unittest_init_command(&command);
	strcpy(command.executable_command, compiler_contex->compiler_path);

	unittest_attach_args(&command, compiler_contex->compiler);
	unittest_attach_args(&command, compiler_contex->compiler_flags);
	unittest_attach_args(&command, file);

	for (size_t i = 0; i < amount_objs; i++)
		unittest_attach_args(&command, objs[i]);

#ifndef NDEBUG /* For debugin the framework */
	unittest_attach_args(&command, "-L./lib");
#endif

	unittest_attach_args(&command, LIB_UNITTEST);
	unittest_attach_args(&command, LIB_EXCEPT);

	if (unittest_link_extra_args)
		unittest_attach_args(&command, unittest_link_extra_args_buff);
	
	unittest_attach_args(&command, "-o");
	unittest_attach_args(&command, out);
	
	/* Recompile without unittest_recompile feature active */
	unittest_attach_args(&command, "-DNUNITTEST_RECOMPILE");

	return unittest_execute(&command);
}
