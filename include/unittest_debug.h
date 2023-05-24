/*!
  @file unittest_debug.h
  @brief This is the interface for a C unit testing framework. It includes macros for controlling debug
  output and logging messages to the output stream. The provided macros allow you to activate the mute mode
  and redirect the output to /dev/null, as well as log new information to the output stream. This interface is
  designed to assist in debugging and logging during unit testing.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License
*/

#ifndef UNITTEST_DEBUG_INCLUDED
#define UNITTEST_DEBUG_INCLUDED

#include <fcntl.h>
#include <stdio.h>

extern int unittest_fd_stdout;

/* MUTE_ACTIVE: To active the mute mode */
#define MUTE_ACTIVE()           \
	unittest_mute_mode = 1; \
	unittest_fd_stdout = open("/dev/null", O_WRONLY)

/* LOG new information */
#define LOG(M, ...) dprintf(unittest_fd_stdout, M __VA_OPT__(, ) __VA_ARGS__)

#endif
