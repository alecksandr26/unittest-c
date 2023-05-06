#include <malloc.h>
#include "../../include/unittest.h"

TESTCASE(TestingMalloc2)
{
	/* Construct the test case */
	int *pointer = NULL, amount = 10;
	
	/* Each test is isolated */
	TEST(MallocNotNull) {
		pointer = malloc(sizeof(int) * amount);
		ASSERT(pointer != NULL);
		free(pointer);
	}

	TEST(ShouldBeNull) {
		ASSERT(pointer == NULL);
	}

	TEST(AmountShouldBe10) {
		ASSERT(amount == 10);
	}


	TEST(AnotherTest) {
		ASSERT(pointer == NULL);
	}

	TEST(AnotherTest2) {
		ASSERT(amount == 10);
	}
} ENDTESTCASE

NEW_SUIT(SecondSuit2, TestingMalloc2);
