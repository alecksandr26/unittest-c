#include "../../include/unittest.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	Test(first_test)
	{ /* First Test */
		var++;
		assert(var == 2);
	}

	Test(second_test)
	{ /* Second test */
		/* Do your assertions */
		assert(var == 1);
	}
}
EndTestCase

/* Test a simple function */
TestCase(Testfoo)
{
	/* Execute for each test */
	size_t amount = 100;
	float *arr    = malloc(sizeof(float) * amount);
	float  sum    = 0.0;

	Test(simple_sum)
	{
		for (size_t i = 0; i < amount; i++)
			arr[i] = ((float) i) / 100;

		sum = foo(arr, amount);
		assert(sum == (float) 49.500004);
	}

	free(arr);
}
EndTestCase

	/* First suit */
	NEW_SUIT(FirstSuit, Testfoo, NewCase);

TestCase(TestingMalloc)
{
	/* Construct the test case */
	int *pointer = NULL, amount = 10;

	/* Each test is isolated */
	Test(MallocNotNull)
	{
		pointer = malloc(sizeof(int) * amount);
		assert(pointer != NULL);
		free(pointer);
	}

	Test(ShouldBeNull) { assert(pointer == NULL); }
}
EndTestCase

	NEW_SUIT(SecondSuit, TestingMalloc);

int main(void)
{
	CATCH(FirstSuit, SecondSuit);
	/* Better */

	RUN();
}
