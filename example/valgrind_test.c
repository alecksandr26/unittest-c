#include "../include/unittest.h"

#include <stdio.h>

#undef TEST_OUT
#define TEST_OUT "valgrind_test.out"

#undef TEST_DIR
#define TEST_DIR "dir5/"

int main()
{
#undef UNITTEST_RECOMPILE
#define UNITTEST_RECOMPILE 1

	INCLUDE_SUIT("simpletest.c", MySuit);

	ACTIVE_VALGRIND();

	RUN();
	return 0;
}
