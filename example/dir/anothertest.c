#include <malloc.h>
#include "../../include/unittest.h"

TestCase(TestingMalloc2)
{
	/* Construct the test case */
	int *pointer = NULL, amount = 10;
	
	/* Each test is isolated */
	Test(MallocNotNull) {
		pointer = malloc(sizeof(int) * amount);
		ASSERT(pointer != NULL);
		free(pointer);
	}

	Test(ShouldBeNull) {
		ASSERT(pointer == NULL);
	}

	Test(AmountShouldBe10) {
		ASSERT(amount == 10);
	}


	Test(AnotherTest) {
		ASSERT(pointer == NULL);
	}

	Test(AnotherTest2) {
		ASSERT(amount == 10);
	}
} EndTestCase

NEW_SUIT(SecondSuit2, TestingMalloc2);
