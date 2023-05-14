#include "../include/unittest.h"

#include <stdio.h>

#undef TEST_OUT
#define TEST_OUT "testc.out"

#undef TEST_DIR
#define TEST_DIR "dir4/"

int main()
{
#undef UNITTEST_RECOMPILE
#define UNITTEST_RECOMPILE 1

	INCLUDE_SUIT("simpletest.c", MySuit);

	RUN();
	return 0;
}
