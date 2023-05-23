#include "../../include/unittest.h"

/* Testing external code */
TESTCASE(TestingFoo)
{
	/* boilerplate code */
	extern int foo(int a, int b); /* It should works */

	TEST(Test1OfFoo) {
		int res = foo(10, 20);
		ASSERT(res == 30, "Testing foo");
	}
} ENDTESTCASE

