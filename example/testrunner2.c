/* To compile run:
   cc -ggdb -c obj/foo.c -o obj/foo.o && cc -ggdb testrunner2.c -o testrunner2  -lunittest && ./testrunner2
*/

#include <stdio.h>

#define TEST_DIR "dir/"
#define UNITTEST_RECOMPILE
#include <unittest.h>


int main(void)
{
	INCLUDE_TESTCASE("simpletest.c", SimpleTest);
	INCLUDE_SUIT("simpletest.c", MySuit);
	INCLUDE_TESTCASE("test_foo.c", TestingFoo);

	ATTACH_EXTRA_COMPILE_FLAGS("-ggdb");
	
	ATTACH_EXTRA_LINKING_FLAGS("obj/foo.o");
	
	ACTIVE_VALGRIND(true);
		
	/* Run the selected testcases or suits */
	RUN(SimpleTest, MySuit, TestingFoo);
	
	return unittest_ret;
}






