#include <malloc.h>
#include <assert.h>
#include "../../../include/unittest.h"


float foo(float *arr, size_t n)
{
	float sum = 0.0;
	for (size_t i = 0; i < n; i++)
		sum += arr[i];
	return sum;
}


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

		printf("total isolated: %f\n", sum);
		
		assert(sum == (float) 49.500004);
	}
	
	free(arr);
} EndTestCase


TestCase(TestingMalloc)
{
	/* Construct the test case */
	int *pointer = NULL, amount = 10;
	
	/* Each test is isolated */
	Test(MallocNotNull) {
		pointer = malloc(sizeof(int) * amount);
		assert(pointer != NULL);
		free(pointer);
	}

	Test(ShouldBeNull) {
		assert(pointer == NULL);
	}
} EndTestCase


/* Creates a new test cases */
TestCase(NewCase)
{
	/* Construct the tests case */
	int var = 1;
	
	/* Start testing */
	Test(first_test) {	/* First Test */
		var++;
		assert(var == 2);
		printf("Isolated in %s: %i\n", tframe.current_test, var);
	}

	Test(second_test) { 	/* Second test */
		/* Do your assertions */
		assert(var == 1);
		printf("Isolated in %s: %i\n", tframe.current_test, var);
	}
} EndTestCase

NEW_SUIT(FirstSuit, TestingMalloc, NewCase);
NEW_SUIT(SecondSuit, Testfoo);
