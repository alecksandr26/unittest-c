#define TEST_DIR "test_dir/"
#define TEST_OUT "../bin/test_compile_fails.out"
#define UNITTEST_RECOMPILE

#include "../../include/unittest.h"

#include <assert.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	INCLUDE_SUIT("compile_error.c", MySuit);

	ACTIVE_VALGRIND(false);
	MUTE_ACTIVE(true);
	
	RUN(MySuit);

	/* To test recompilation we need to know which process we are */
	if (unittest_running_tests) {
		/* Child process */
		assert(unittest_ret == -1); /* The tests should success */

	} else {
		/* The father program */

		/* Do a smiple assserts */
		extern char unittest_testdir[DIR_SIZE_NAME],
			unittest_objdir[DIR_SIZE_NAME];

		assert(access(unittest_testdir, F_OK) == 0);
		assert(unittest_ret == 0); /* The tests should success */
		// assert(unittest_run_valgrind == 1); /* We are running valgrind */

		assert(access(unittest_objdir, F_OK) == 0); /* It should be created */
	}

	return 0;
}
