#include "../../include/unittest.h"


/* Creates a new test cases */
TESTCASE(NewCase2)
{
	/* Construct the tests case */
	int var = 1;
	
	/* Start testing */
	TEST(first_test) {	/* First TEST */
		var += 2;
		ASSERT(var == 3);
	}

	TEST(second_test) { 	/* Second test */
		/* Do your assertions */
		var++;
		ASSERT(var == 2);
		var++;
		ASSERT(var == 3);
	}

	TEST(third_test) {
		
		ASSERT(var == 1, "Should be one >:|"); /* Stops executing */

		// ASSERT(0, "This other assert shoun't bee executed");
	}
} ENDTESTCASE

