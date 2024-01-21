
#define TEST_DIR "tests_for_testing2/"
#define TEST_OUT "test_compile_fails.out"
#define UNITTEST_RECOMPILE 1
#include "../../include/unittest.h"

#include <assert.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	INCLUDE_SUIT("simpletest.c", MySuit);
	// ACTIVE_VALGRIND();

	// MUTE_ACTIVE();
	RUN();

	/* To test recompilation we need to know which process we are */
	if (unittest_running_tests) {
		/* Child process */
		assert(unittest_ret == 0); /* The tests should success */
	} else {
		/* The father program */

		/* Do a smiple assserts */
		extern char unittest_testdir[DIR_SIZE_NAME], unittest_objdir[DIR_SIZE_NAME];

		assert(access(unittest_testdir, F_OK) == 0);
		assert(unittest_ret == 0); /* The tests should success */
		// assert(unittest_run_valgrind == 1); /* We are running valgrind */

		assert(access(unittest_objdir, F_OK) == 0); /* It should be created */
	}

	return 0;
}
