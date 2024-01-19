#include "../include/unittest.h"

#include <stdio.h>

#undef TEST_OUT
#define TEST_OUT "valgrind_test.out"

#undef TEST_DIR
#define TEST_DIR "dir5/"

#undef UNITTEST_RECOMPILE
#define UNITTEST_RECOMPILE 1

int main()
{
	INCLUDE_SUIT("simpletest.c", MySuit);
	INCLUDE_TEST_CASE("secondtest.c", TestingFoo);
	
	ACTIVE_VALGRIND();

	/*
	  COMPILE: cc -c obj/foo.c -o obj/foo.o, to be able to run this example
	 */
	
	ATTACH_EXTRA_LINKING_FLAGS("obj/foo.o");
	
	
	RUN();

	return unittest_ret;
}
