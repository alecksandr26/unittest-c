#include "../../include/unittest.h"


/* Creates a new test cases */
TestCase(NewCase2)
{
	/* Construct the tests case */
	int var = 1;
	
	/* Start testing */
	Test(first_test) {	/* First Test */
		var += 2;
		ASSERT(var == 3);
	}

	Test(second_test) { 	/* Second test */
		/* Do your assertions */
		var++;
		ASSERT(var == 2);
		var++;
		ASSERT(var == 3);
	}

	Test(third_test) {
		
		ASSERT(var == 1, "Should be one >:|"); /* Stops executing */

		// ASSERT(0, "This other assert shoun't bee executed");
	}
} EndTestCase

