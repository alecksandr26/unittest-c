#include "../../include/unittest.h"

#include <assert.h>
#include <stdio.h>

#undef TEST_OUT
#define TEST_OUT "test_compile_fails.out"

#undef TEST_DIR
#define TEST_DIR "tests_for_testing2/"

#undef UNITTEST_RECOMPILE
#define UNITTEST_RECOMPILE 1

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
		extern char unittest_testdir[100], unittest_objdir[100];

		assert(access(unittest_testdir, F_OK) == 0);
		assert(unittest_ret == 0); /* The tests should success */
		// assert(unittest_run_valgrind == 1); /* We are running valgrind */

		assert(access(unittest_objdir, F_OK) == 0); /* It should be created */
	}

	return 0;
}
