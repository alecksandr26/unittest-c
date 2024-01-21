#include "../../include/unittest.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

TESTCASE(Checking)
{
	/* This test will faild */
	int var1 = 1, var2 = 2;

	struct person {
		char name[100];
		int age;
	};
	
	TEST(NormalAssertion) { ASSERT(var1 == var2, "Testing the message"); }
	
	TEST(ComparisonAssertion) {
		ASSERT_EQ(var1, 3, "This is a message");
	}

	struct person p1, p2;

	p1.age = 11;
	p2.age = 11;
	memset(p1.name, 0, sizeof(p1.name));
	memset(p2.name, 0, sizeof(p2.name));
	strcpy(p1.name, "Pedrito");
	strcpy(p2.name, "Pedrito");
	
	TEST(ComparsionAssertionEspecial) {
		ASSERT_NEQ(p1, p2, "Cheking if this works");
	}

	TEST(ComparsionLesserThan) {
		ASSERT_GT(var1, var2);
	}
	
} ENDTESTCASE

int main(void)
{
	/* MUTE_ACTIVE(true); */

	RUN(Checking);

	/* It supouse to have an failed assertion */
	assert(unittest_ret == -1);

	/* A few simple assertinos */
	assert(Checking.amount == 2);
	assert(Checking.amount_failed == 2);
	assert(Checking.failed_info[0].expr != NULL);
	assert(Checking.failed_info[0].unitcase != NULL);
	assert(Checking.failed_info[0].file != NULL);
	assert(Checking.failed_info[0].msg != NULL);
	assert(Checking.failed_info[0].line == 11);

	return 0;
}
