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

TESTCASE(TestingExcept)
{
	int var1 = 1, var2 = 2;

	TEST(SimpleExcept) { EXPECT(var1 != var2, "Should be true"); }

	TEST(MultileExpects)
	{
		EXPECT(var1 == var2, "Should be false");
		EXPECT(var1 == var2, "Should be false2");
	}

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
	
	TEST(ComparsionExpectEspecial)
	{
		EXPECT_EQ(p1, p2, "Cheking if this works");
		EXPECT_NEQ(p1, p2, "Cheking if this works");
	}

	int var3 = 7, var4 = 6;

	TEST(ComparsionLesserEqualThan) { EXPECT_LE(var3, var4); }

	TEST(ComparsionGreaterThan) { EXPECT_GT(var3, var4); }

	TEST(ComparsionGreaterThan) { EXPECT_GE(var3, 9); }

	char *str1 = "Hello World";
	char *str2 = "Hello World";

	TEST(ComparsionGreaterThan) { EXPECT_STR_EQ(str1, str2); }

	TEST(ComparsionGreaterThan) { EXPECT_STR_NEQ(str1, str2); }

	TEST(ComparisonNear) {
		double x = 0.314;
		double y = 0.315;
		EXPECT_NEAR(x, y, 1e-3, "Lets see if this thign works ");
	}


	TEST(ExpectsThrowingExcept) {
		EXPECT_THROW({
				throws_expection();
			}, ExceptBadAlloc, "Just Cheking that it throws the actual exception");
	}

	TEST(ExpectsThrowingExcept2) {
		EXPECT_ANY_THROW({
				do_nothing();
			}, "Just Cheking that it doens't through nothing");
	}
	

	TEST(ExpectsThrowingExcept3) {
		EXPECT_NO_THROW({
				throws_expection();
			}, "Just Cheking that it doens't through nothing");
	}
}
ENDTESTCASE

int main(void)
{
	MUTE_ACTIVE(true);
	RUN(TestingExcept);

	assert(unittest_ret == 1);

	assert(TestingExcept.amount == 12);

	assert(TestingExcept.info.number_warning_expects == 10);
	assert(TestingExcept.info.unitcase != NULL);
	assert(TestingExcept.info.file != NULL);

	assert(TestingExcept.info.warning_expects[0].msg != NULL);
	assert(TestingExcept.info.warning_expects[0].line == 26);

	return 0;
}
