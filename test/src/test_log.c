
#include <assert.h>
#include "../../include/unittest.h"


/* Creates a new test cases */
TESTCASE(NewCase)
{
	/* Construct the tests case */
	int var = 1;

	/* Start testing */
	TEST(first_test)
	{ /* First TEST */
		var++;

		LOG("%i\n", var); /* To print inforamtion */
		
		/* This thing is unmuted so it should pass this simple assert */
		extern int unittest_fd_stdout;
		assert(unittest_fd_stdout == 1); /* It should be 1 */
		
		ASSERT(var == 2);
	}

	TEST(second_test)
	{ /* Second test */
		/* Do your assertions */
		ASSERT(var == 1);
	}
} ENDTESTCASE




int main()
{
	/* Simple demostration of the log macro works */
	

	RUN(NewCase);
}
