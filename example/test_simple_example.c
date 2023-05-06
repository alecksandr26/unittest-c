#include <unittest.h>
#include <stdio.h>

TESTCASE(Checking)
{
	/* This test will faild */
	TEST(False) {
		ASSERT(1 == 0, "Testing the message");
	}
} ENDTESTCASE


NEW_SUIT(MySuit, Checking);

int main(void)
{

	RUN(MySuit);

	return 0;
}
