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


	void *ptr = NULL;
	/* int num; */
	int num = 9;

	TEST(TestBreaks) {
		ASSERT(ptr == NULL, "It is null");
		int n = num + 1;

		if (n == 10)
			LOG("Hello brother");
		
		/* int n = *((int *) ptr); */
		/* int n = *ptr; */
	}
	
} ENDTESTCASE

