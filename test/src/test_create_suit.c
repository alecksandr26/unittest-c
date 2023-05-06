#include "../../include/unittest.h"

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
		ASSERT(var == 1);
	}

	Test(second_test)
	{ /* Second test */
		/* Do your assertions */
		ASSERT(var == 1);
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
		// ASSERT(sum == (float) 49.500004);
		ASSERT(sum == (float) 49.500000);
	}

	free(arr);
}
EndTestCase

	/* Creats a new suit for testing */
	NEW_SUIT(SimpleSuit, Testfoo, NewCase);

int main(void)
{
	CATCH(SimpleSuit);
	RUN();

	// RUN(SimpleSuit);

	return 0;
}
