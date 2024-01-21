
#define TEST_DIR "dir5/"
#define TEST_OUT "valgrind_test.out"
#define UNITTEST_RECOMPILE 
#include "../include/unittest.h"

#include <stdio.h>


int main()
{
	INCLUDE_SUIT("simpletest.c", MySuit);
	INCLUDE_TESTCASE("secondtest.c", TestingFoo);
	
	ACTIVE_VALGRIND(true);
	/*
	  COMPILE: cc -c obj/foo.c -o obj/foo.o, to be able to run this example
	 */
	
	ATTACH_EXTRA_LINKING_FLAGS("obj/foo.o");
	
	
	RUN();

	return unittest_ret;
}
