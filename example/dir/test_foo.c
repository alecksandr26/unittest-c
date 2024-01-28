

/* Simple example to test the foo  */

#include <unittest.h>

TESTCASE(TestingFoo) {

	extern int foo(void);

	TEST(FooReturn) {
		ASSERT_EQ(foo(), 1, "foo must to return 1");
	}
} ENDTESTCASE

