/*!
  @file command.c
  @brief This is the souce code of the implementation of the module 'unittest_command.h'.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <trycatch.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "../include/unittest_command.h"

Except UnittestTooLongCommand = {"Error creating a really big command"};
Except UnittestTooMuchArgs = {"Error too much arguments"};

/* get_command_str: To get the plain string version of the command. */
static void get_command_str(const UnitCommand *command, char *str, size_t str_size)
{
	assert(command != NULL && "Can't be null");
	assert(str != NULL && "Can't be null");
	assert(str_size > 0 && "Can't process zero arguments");

	memset(str, 0, str_size);
	
	size_t index = strlen(command->executable_command);
	strcat(str, command->executable_command);
	str[index] = ' ';
	str += ++index;

	if (index >= COMMAND_SIZE)
		throw(UnittestTooLongCommand);

	for (size_t i = 0; i < command->nargs; i++) {
		index = strlen(command->args[i]);
		strcat(str, command->executable_command);
		str[index] = ' ';
		str += ++index;
		
		if (index >= COMMAND_SIZE)
			throw(UnittestTooLongCommand);
	}
}

/* abort_command_execution: To abort the execution of the program by an error of an command. */
static void abort_command_execution(const UnitCommand *command)
{
	assert(command != NULL && "Can't be null");
	
	char command_str[COMMAND_SIZE];
	get_command_str(command, command_str, COMMAND_SIZE);
	
	fprintf(stderr, "Error while executing `%s`: fork: %s",
		command_str,
		strerror(errno));
	fprintf(stderr, "Aborting....");
	abort();
}

/* unittest_attach_args: To attach arguments to the command. */
void unittest_attach_args(UnitCommand *command, const char *args)
{
	size_t n = strlen(args);

	assert(command != NULL && "Can't be null");
	assert(command->buff_ptr != NULL && "command not initilized");
	assert(n > 0 && "Can't set empty args");

	if (command->args_buff - command->buff_ptr <= n)
		throw(UnittestTooMuchArgs);

	for (size_t i = 0; i < n; i++) {
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
		int ret = execv(command->executable_command, (char * const *) command->args);
		
		if (ret == -1)
			abort_command_execution(command);

		assert(0 && "Shouldn't exectue this part");
	} else {	   /* Parent process */
		/* waits the child process finished its excecution */
		pid_t child_pid = waitpid(pid, &status, 0); 
		if (child_pid == -1)
			abort_command_execution(command);
	}

	return status;
}


