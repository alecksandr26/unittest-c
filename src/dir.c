/*
  @file dir.c
  @brief This is the source code for the component 'unittest_dir.h'.

  @author Erick Carrillo.
  @copyright Copyright (C) 2022, Erick Alejandro Carrillo López, All rights reserved.
  @license This project is released under the MIT License.
*/

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <trycatch.h>

#include "../include/unittest_def.h"
#include "../include/unittest_dir.h"

Except UnittestErrorTestBaseDoesntExist = {
	"Error the default \"TEST_DIR\" doesn't exist"};

bool unittest_fetched_files_name = false;

#ifndef NDEBUG
bool is_root_folder = false;
#endif

char unittest_basedir[FILE_SIZE_NAME];
char unittest_file[FILE_SIZE_NAME];
char unittest_outfile[FILE_SIZE_NAME];
char unittest_testdir[FILE_SIZE_NAME];
char unittest_objdir[FILE_SIZE_NAME];
char unittest_hashed_file[FILE_SIZE_NAME];


/* get_basedir: Gets the base dir from path to a file */
static void get_basedir(const char *file, char *basedir)
{
	int n = strlen(file);

	/* Iterates until finds a '/' */
	for (; n >= 0 && file[n] != '/'; n--)
		;

	if (n > 0) memcpy(basedir, file, n + 1);
}

/* executing_from_basedir: To know if im executing the program in the basedir */
static bool executing_from_basedir(const char *file)
{
	/* Get the current working directory */
	char cwd[1024], basedir[255], fdir[255]; /* First dir */
	int  n, m;

	memset(cwd, 0, sizeof(cwd));
	memset(basedir, 0, sizeof(basedir));

	get_basedir(file, basedir);
	getcwd(cwd, sizeof(cwd));

	/* Count the amount of slashes in basedir */
	m = 0;
	for (size_t i = 0; i < strlen(basedir); i++)
		if (basedir[i] == '/') m++;

	for (n = strlen(cwd); n >= 0; n--) {
		if (cwd[n] == '/') m--;

		if (m == 0) break;
	}

	memset(fdir, 0, sizeof(fdir));
	memcpy(fdir, cwd + n + 1, strlen(cwd) - n);
	fdir[strlen(fdir)] = '/';

	if (strcmp(fdir, basedir) == 0) return true;
#ifndef NDEBUG
	else is_root_folder = true;
#endif

	/* we are in another directory */
	return false;
}

/* unittest_fetch_filesname: This functions gets the paths for the needed recompilation. */
void unittest_fetch_filesname(const char *file, const char *outfile, const char *testdir,
			      const char *objdir, const char *hashed_file)
{
	if (unittest_fetched_files_name) return;

	memset(unittest_file, 0, sizeof(unittest_file));
	memset(unittest_basedir, 0, sizeof(unittest_basedir));
	memset(unittest_outfile, 0, sizeof(unittest_outfile));

	/* Patch all the filesname */
	if (executing_from_basedir(file)) { /* Try to find that we are in the basedir */
		int i;

		/* Try to find where it is '/' */
		for (i = strlen(file); i >= 0 && file[i] != '/'; i--)
			;
		strcpy(unittest_file, file + i + 1);
	} else {
		get_basedir(file, unittest_basedir); /* get the basedir */
		strcpy(unittest_file, file);
	}

	/* Dump the basedir and fill all the variabels */
	strcpy(unittest_outfile, unittest_basedir);
	strcat(unittest_outfile, outfile);

	strcpy(unittest_testdir, unittest_basedir);
	strcat(unittest_testdir, testdir);

	strcpy(unittest_objdir, unittest_testdir);
	strcat(unittest_objdir, objdir);

	strcpy(unittest_hashed_file, unittest_testdir);
	strcat(unittest_hashed_file, hashed_file);

	unittest_fetched_files_name = true;
}

void unittest_check_testdir_exist(void)
{
	if (access(unittest_testdir, F_OK) != 0) throw(UnittestErrorTestBaseDoesntExist);
}

