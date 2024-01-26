#include "../../include/unittest.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>


TESTCASE(TestingExcept) {
	int var1 = 1, var2 = 2;
	
	TEST(SimpleExcept) {
		EXPECT(var1 != var2, "Should be true");
	}
	
	TEST(MultileExpects) {
		EXPECT(var1 == var2, "Should be false");
		EXPECT(var1 == var2, "Should be false2");
	}

	struct person {
		char name[100];
		int age;
	};
	
	struct person p1, p2;

	p1.age = 11;
	p2.age = 11;
	memset(p1.name, 0, sizeof(p1.name));
	memset(p2.name, 0, sizeof(p2.name));
	strcpy(p1.name, "Pedrito");
	strcpy(p2.name, "Pedrito");
	
	TEST(ComparsionExpectEspecial) {
		EXPECT_EQ(p1, p2, "Cheking if this works");
		EXPECT_NEQ(p1, p2, "Cheking if this works");
	}


	int var3 = 7, var4 = 6;

	TEST(ComparsionLesserEqualThan) {
		EXPECT_LE(var3, var4);
	}

	TEST(ComparsionGreaterThan) {
		EXPECT_GT(var3, var4);
	}

	TEST(ComparsionGreaterThan) {
		EXPECT_GE(var3, 9);
	}

	char *str1 = "Hello World";
	char *str2 = "Hello World";

	TEST(ComparsionGreaterThan) {
		EXPECT_STR_EQ(str1, str2);
	}

	TEST(ComparsionGreaterThan) {
		EXPECT_STR_NEQ(str1, str2);
	}
} ENDTESTCASE

int main(void)
{
	MUTE_ACTIVE(0);
	RUN(TestingExcept);

	assert(unittest_ret == 1);

	
	assert(TestingExcept.amount == 8);

	assert(TestingExcept.failed_info.number_warning_expects == 6);
	assert(TestingExcept.failed_info.unitcase != NULL);
	assert(TestingExcept.failed_info.file != NULL);

	assert(TestingExcept.failed_info.warning_expects[0].msg != NULL);
	assert(TestingExcept.failed_info.warning_expects[0].line == 16);
	
	
	return 0;
}




