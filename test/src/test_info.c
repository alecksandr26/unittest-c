#include "../../include/unittest.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

TESTCASE(Checking)
{
	/* This test will faild */
	int var1 = 1, var2 = 2;
	
	TEST(NormalAssertion) {
		INFO_EXPR(var1 == var2);
		
		ASSERT(var1 == var2, "Testing the message");
	}
	
} ENDTESTCASE


int main(void)
{
	MUTE_ACTIVE(true);

	RUN(Checking);
	
	return 0;
}




