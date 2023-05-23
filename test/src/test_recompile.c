#include "../../include/unittest.h"

#undef TEST_OUT
#define TEST_OUT "test_recompile.out"

#undef TEST_DIR
#define TEST_DIR "tests_for_testing/"

#undef UNITTEST_RECOMPILE
#define UNITTEST_RECOMPILE 1

int main()
{
	INCLUDE_SUIT("simpletest.c", MySuit);
	ACTIVE_VALGRIND();
	
	MUTE_ACTIVE();
	
	RUN();
	
	return 0;
}

