/* To compile run:
   cc -o testrunner testrunner.c dir/simpletest.c -lunittest && ./testrunner
*/

#include <stdio.h>

#define TEST_DIR "dir/"
#include <unittest.h>

int main(void)
{
	// Include a testcase
	INCLUDE_TESTCASE("simpletest.c", SimpleTest);
	
	// Include a suit
	INCLUDE_SUIT("simpletest.c", MySuit);

	/* Run the selected testcases or suits */
	RUN(SimpleTest, MySuit);
	
	return unittest_ret;
}
