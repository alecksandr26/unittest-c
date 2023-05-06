
#include "../../include/unittest.h"

#include <stdio.h>

TestCase(Checking)
{
	/* This test will faild */
	Test(False) { ASSERT(1 == 0, "Testing the message"); }
}
EndTestCase

	int
	main(void)
{

	RUN(Checking);

	return 0;
}
