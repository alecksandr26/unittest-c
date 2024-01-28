// simpletest.c
#include <unittest.h>

TESTCASE(SimpleTest) {
	// Set up any boilerplate code for all tests in the test case
	int var = 1;

	// Define individual tests using the TEST macro
	TEST(Test1) {
		// Use ASSERT macro to check if var is equal to 1
		ASSERT_EQ(var, 1, "It should be one");
	}

	TEST(Test2) {
		ASSERT(var > 0, "It should be greater than zero");
	}

	TEST(Test3) {
		ASSERT(var < 2, "It should be lesser than 2");
	}

	TEST(Test4) {
		ASSERT(var != 0, "It should not be zero");
	}
} ENDTESTCASE


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

TESTCASE(MyTestCases2)
{
	// Set up any boilerplate code for all tests in the test case
	int y = 100;

	// Define individual tests using the TEST macro
	TEST(Test3) {
		// Use ASSERT macro to check if y equals 100
		ASSERT(y == 100, "y should equal 100");
	}

	TEST(Test4) {
		// Use ASSERT macro to check if y is greater than or equal to 50
		ASSERT(y >= 50, "y should be greater than or equal to 50");
	}
} ENDTESTCASE

SUIT(MySuit, MyTestCases1, MyTestCases2);
