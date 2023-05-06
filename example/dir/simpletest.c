#include <malloc.h>
#include "../../include/unittest.h"


float foo(float *arr, size_t n)
{
	float sum = 0.0;
	for (size_t i = 0; i < n; i++)
		sum += arr[i];
	
	return sum;
}

/* Creates a new test cases */
TESTCASE(NewCase)
{
	/* Construct the tests case */
	int var = 1;
	
	/* Start testing */
	TEST(first_test) {	/* First TEST */
		var += 2;
		ASSERT(var == 3);
	}

	TEST(second_test) { 	/* Second test */
		/* Do your assertions */
		var++;
		ASSERT(var == 2);
		var++;
		ASSERT(var == 3);
	}

	TEST(third_test) {
		
		ASSERT(var == 1, "Should be one >:|"); /* Stops executing */

		// ASSERT(0, "This other assert shoun't bee executed");
	}
} ENDTESTCASE


/* TEST a simple function */
TESTCASE(Testfoo)
{
	/* Execute for each test */
	size_t amount = 100;
	float *arr = malloc(sizeof(float) * amount);
	float sum = 0.0;
	
	TEST(simple_sum) {
		for (size_t i = 0; i < amount; i++)
			arr[i] = ((float) i) / 100;

		sum = foo(arr, amount);
		ASSERT(sum == (float) 49.500004);
	}
	
	free(arr);
} ENDTESTCASE

/* First suit */
NEW_SUIT(FirstSuit, Testfoo, NewCase);

TESTCASE(TestingMalloc)
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
		ASSERT(pointer ==  NULL);
	}

	TEST(AmountShouldBe10) {
		ASSERT(amount == 10);
	}


	TEST(AnotherTest) {
		ASSERT(pointer == NULL);
	}
} ENDTESTCASE

NEW_SUIT(SecondSuit, TestingMalloc);
