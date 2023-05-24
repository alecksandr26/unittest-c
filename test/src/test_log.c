
#include "../../include/unittest.h"

#include <assert.h>

TESTCASE(MyTests)
{
	// Set up any boilerplate code for all tests in the test case
	int x = 42;

	// Define individual tests using the TEST macro
	TEST(Test1)
	{
		// Use ASSERT macro to check if x equals 42
		ASSERT(x == 42, "x should equal 42");
	}

	TEST(Test2)
	{
		// Use ASSERT macro to check if x is less than 100
		ASSERT(x < 100, "x should be less than 100");

		// Print the value of x using the LOG macro
		LOG("The value of x is: %i\n", x);
	}
}
ENDTESTCASE

int main()
{
	/* Simple demostration of the log macro works */

	RUN(MyTests);
}
