/*!
  @file command.c
  @brief This is the souce code of the implementation of the module 'unittest_command.h'.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include "../include/unittest_command.h"
#include "../include/unittest_debug.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <trycatch.h>
#include <unistd.h>

/* get_command_str: To get the plain string version of the command. */
static void get_command_str(const UnitCommand *command, char *str, size_t str_size)
{
	assert(command != NULL && "Can't be null");
	assert(str != NULL && "Can't be null");
	assert(str_size > 0 && "Can't process zero arguments");

	memset(str, 0, str_size);

	for (size_t i = 0; i < command->nargs; i++) {
		size_t index = strlen(command->args[i]);
		strcat(str, command->args[i]);
		str[index] = ' ';
		str += ++index;

		assert(index < COMMAND_SIZE &&
		       "Impossible to build the stringable version of the command");
	}
}

/* abort_command_execution: To abort the execution of the program by an error of an
 * command. */
static void abort_command_execution(const UnitCommand *command)
{
	assert(command != NULL && "Can't be null");

	char command_str[COMMAND_SIZE];
	get_command_str(command, command_str, COMMAND_SIZE);

	ABORT("Error while executing `%s`: errno: %s.\n", command_str, strerror(errno));
}

/* unittest_attach_args: To attach arguments to the command. */
void unittest_attach_args(UnitCommand *command, const char *args)
{
	size_t n = strlen(args);

	assert(command != NULL && "Can't be null");
	assert(command->buff_ptr != NULL && "command not initilized");
	assert(n > 0 && "Can't set empty args");

	assert((&command->args_buff[FLAGS_BUFF_SIZE] - command->buff_ptr) > n &&
	       "Must to have enough space to do its operation");

	size_t i = 0;
	while (i < n) {
		command->args[command->nargs++] = command->buff_ptr;

		/* Copy en entiere argument */
		size_t j;
		for (j = 0; i < n && args[i] != ' '; j++)
			command->buff_ptr[j] = args[i++];

		command->buff_ptr[j] = '\0';
		command->buff_ptr += j + 1;

		/* Iterate until finish or find another arg */
		for (; i < n && args[i] == ' '; i++)
			;
	}
}

/* unittest_execute: To execute the command with the attach arguments. */
int unittest_execute(const UnitCommand *command)
{
	assert(command != NULL && "Can't be null");

	int   status;
	pid_t pid = fork(); /* Creates the child process */
	if (pid == -1) {
		abort_command_execution(command);

	} else if (pid == 0) { /* Child process */
		/* Wtf with that cast */
		int ret =
			execv(command->executable_command, (char *const *) command->args);

		if (ret == -1) abort_command_execution(command);

		assert(0 && "Shouldn't exectue this part");
	} else { /* Parent process */
		/* waits the child process finished its excecution */
		pid_t child_pid = waitpid(pid, &status, 0);
		if (child_pid == -1) abort_command_execution(command);
	}

	return status;
}

/* unittest_init_command: To inialized a command structure with it default attributes. */
void unittest_init_command(UnitCommand *command)
{
	assert(command != NULL && "Can't be null");
	memset(command, 0, sizeof(UnitCommand));
	command->buff_ptr = command->args_buff;
}
