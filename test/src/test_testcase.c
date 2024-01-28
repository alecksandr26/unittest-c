
#include <unittest.h>

TESTCASE(MyTestCases1)
{
	// Set up any boilerplate code for all tests in the test case
	int x = 42;
	
	// Define individual tests using the TEST macro
	TEST(Test1) {
		// Use ASSERT macro to check if x equals 42
		ASSERT(x == 42, "x should equal 42");
	}

	TEST(Test2) {
		// Use ASSERT macro to check if x is less than 100
		ASSERT(x < 100, "x should be less than 100");
	}
	
} ENDTESTCASE

int main(void)
{
	RUN(MyTestCases1);
	
	
	return 0;
}
