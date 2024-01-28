#include "../../include/unittest.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <trycatch.h>

void throws_expection(void)
{
	throw(ExceptLogicalError, "throwing logical error");
}

void do_nothing(void)
{
	
}

TESTCASE(Checking)
{
	/* This test will faild */
	int var1 = 1, var2 = 2;

	TEST(NormalAssertion) { ASSERT(var1 != var2, "Testing the message"); }

	TEST(ComparisonAssertion) { ASSERT_EQ(var1, 3, "This is a message"); }

	struct person {
		char name[100];
		int  age;
	};

	struct person p1, p2;

	p1.age = 11;
	p2.age = 11;
	memset(p1.name, 0, sizeof(p1.name));
	memset(p2.name, 0, sizeof(p2.name));
	strcpy(p1.name, "Pedrito");
	strcpy(p2.name, "Pedrito");

	TEST(ComparsionAssertionEspecial) { ASSERT_NEQ(p1, p2, "Cheking if this works"); }

	TEST(ComparsionLesserThan) { ASSERT_LT(var1, var2); }

	int var3 = 7, var4 = 6;

	TEST(ComparsionLesserEqualThan) { ASSERT_LE(var3, var4); }

	TEST(ComparsionGreaterThan) { ASSERT_GT(var3, var4); }

	TEST(ComparsionGreaterThan) { ASSERT_GE(var3, 9); }

	char *str1 = "Hello World";
	char *str2 = "Hello World";

	TEST(ComparsionGreaterThan) { ASSERT_STR_EQ(str1, str2); }

	TEST(ComparsionGreaterThan) { ASSERT_STR_NEQ(str1, str2); }
	
	TEST(ComparisonNear) {
		double x = 0.314;
		double y = 0.315;
		ASSERT_NEAR(x, y, 1e-2, "Lets see if this thign works ");
	}


	TEST(AssertsThrowingExcept) {
		ASSERT_THROW({
				throws_expection();
			}, ExceptBadAlloc, "Just Cheking that it throws the actual exception");
	}

	TEST(AssertsThrowingExcept2) {
		ASSERT_ANY_THROW({
				do_nothing();
			}, "Just Cheking that it doens't through nothing");
	}

	TEST(AssertsThrowingExcept3) {
		ASSERT_NO_THROW({
				throws_expection();
			}, "Just Cheking that it doens't through nothing");
	}
} ENDTESTCASE

int main(void)
{
	MUTE_ACTIVE(true);

	RUN(Checking);

	/* It supouse to have an failed assertion */
	assert(unittest_ret == -1);

	/* A few simple assertinos */
	assert(Checking.amount == 13);

	assert(Checking.info.number_failed_asserts == 8);

	assert(strcmp("var1 == 3, where var1 = 1 and 3 = 3",
		      Checking.info.failed_asserts[0].expr) == 0);

	assert(Checking.info.unitcase != NULL);
	assert(Checking.info.file != NULL);
	assert(Checking.info.failed_asserts[0].msg != NULL);
	assert(Checking.info.failed_asserts[0].line == 25);
	
	return 0;
}
