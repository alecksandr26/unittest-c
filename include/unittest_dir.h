/*
  @file unittest_dir.h
  @brief This is the component in charge of creating the necessary directories for the recompilation
  process, and setting the directories and files names.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License.
*/

#ifndef UNITTEST_DIR_INCLUDED
#define UNITTEST_DIR_INCLUDED

#include <stdbool.h>

#include "unittest_def.h"

#ifndef NDEBUG
extern bool is_root_folder;
#endif
extern char unittest_basedir[FILE_SIZE_NAME];
extern char unittest_file[FILE_SIZE_NAME];
extern char unittest_outfile[FILE_SIZE_NAME];
extern char unittest_testdir[FILE_SIZE_NAME];
extern char unittest_objdir[FILE_SIZE_NAME];
extern char unittest_hashed_file[FILE_SIZE_NAME];

/* unittest_fetch_filesname: This functions gets the paths for the needed recompilation. */
extern  void unittest_fetch_filesname(const char *file, const char *outfile, const char *testdir,
				      const char *objdir, const char *hashed_file);


extern void unittest_check_testdir_exist(void);

#endif












