#include "../../include/unittest.h"

#include <assert.h>
#include <stdio.h>

TESTCASE(Checking)
{
	TEST(True) {
		ASSERT(1 == 1, "Testing the message");
	}
}
ENDTESTCASE


NEW_SUIT(MySuit, Checking);



