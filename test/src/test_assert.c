
#include "../../include/unittest.h"

#include <stdio.h>

TESTCASE(Checking)
{
	/* This test will faild */
	TEST(False) { ASSERT(1 == 0, "Testing the message"); }
}
ENDTESTCASE

int main(void)
{

	RUN(Checking);

	return 0;
}
