/*!
  @file unittest_command.h
  @brief This module contains implementations for executing commands or programs.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_COMMAND_INCLUDED
#define UNITTEST_COMMAND_INCLUDED

#include <assert.h>
#include <string.h>

#include "unittest_def.h"

typedef struct  {
	char executable_command[BINARY_COMMAND_SIZE];
	char *args[MAX_AMOUNT_OF_ARGUMENTS], args_buff[FLAGS_BUFF_SIZE], *buff_ptr;
	size_t nargs;
} UnitCommand;

/* unittest_attach_args: To attach arguments to the command. */
extern void unittest_attach_args(UnitCommand *command, const char *args);

/* unittest_execute: To execute the command with the attach arguments, and return its result. */
extern int unittest_execute(const UnitCommand *command);

/* unittest_init_command: To inialized a command structure with it default attributes. */
inline void unittest_init_command(UnitCommand *command)
{
	assert(command != NULL && "Can't be null");
	memset(command, 0, sizeof(UnitCommand));
	command->buff_ptr = command->args_buff;
}


#endif






