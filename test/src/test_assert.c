#include "../../include/unittest.h"

#include <assert.h>
#include <stdio.h>

TESTCASE(Checking)
{
	/* This test will faild */
	TEST(False) { ASSERT(1 == 0, "Testing the message"); }
} ENDTESTCASE

int main(void)
{
	MUTE_ACTIVE(true);

	RUN(Checking);

	/* It supouse to have an failed assertion */
	assert(unittest_ret == -1);

	/* A fer simple assertinos */
	assert(Checking.amount == 1);
	assert(Checking.amount_failed == 1);
	assert(Checking.failed_info[0].expr != NULL);
	assert(Checking.failed_info[0].unitcase != NULL);
	assert(Checking.failed_info[0].file != NULL);
	assert(Checking.failed_info[0].msg != NULL);
	assert(Checking.failed_info[0].line == 10);

	return 0;
}
