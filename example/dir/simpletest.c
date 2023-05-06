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
TestCase(NewCase)
{
	/* Construct the tests case */
	int var = 1;
	
	/* Start testing */
	Test(first_test) {	/* First Test */
		var += 2;
		ASSERT(var == 3);
	}

	Test(second_test) { 	/* Second test */
		/* Do your assertions */
		var++;
		ASSERT(var == 2);
		var++;
		ASSERT(var == 3);
	}

	Test(third_test) {
		
		ASSERT(var == 1, "Should be one >:|"); /* Stops executing */

		// ASSERT(0, "This other assert shoun't bee executed");
	}
} EndTestCase


/* Test a simple function */
TestCase(Testfoo)
{
	/* Execute for each test */
	size_t amount = 100;
	float *arr = malloc(sizeof(float) * amount);
	float sum = 0.0;
	
	Test(simple_sum) {
		for (size_t i = 0; i < amount; i++)
			arr[i] = ((float) i) / 100;

		sum = foo(arr, amount);
		ASSERT(sum == (float) 49.500004);
	}
	
	free(arr);
} EndTestCase

/* First suit */
NEW_SUIT(FirstSuit, Testfoo, NewCase);

TestCase(TestingMalloc)
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
		ASSERT(pointer ==  NULL);
	}

	Test(AmountShouldBe10) {
		ASSERT(amount == 10);
	}


	Test(AnotherTest) {
		ASSERT(pointer == NULL);
	}
} EndTestCase

NEW_SUIT(SecondSuit, TestingMalloc);
