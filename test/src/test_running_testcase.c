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

/* TEST a simple function */
TESTCASE(Testfoo)
{
	/* Execute for each test */
	size_t amount = 100;
	float *arr    = malloc(sizeof(float) * amount);
	float  sum    = 0.0;

	TEST(simple_sum)
	{
		for (size_t i = 0; i < amount; i++)
			arr[i] = ((float) i) / 100;

		sum = foo(arr, amount);

		ASSERT(sum == (float) 49.500004);
	}

	free(arr);
}
ENDTESTCASE

TESTCASE(TestingMalloc)
{
	/* Construct the test case */
	int *pointer = NULL, amount = 10;

	/* Each test is isolated */
	TEST(MallocNotNull)
	{
		pointer = malloc(sizeof(int) * amount);
		ASSERT(pointer != NULL);
		free(pointer);
	}

	TEST(ShouldBeNull) { ASSERT(pointer == NULL); }
}
ENDTESTCASE

/* Creates a new test cases */
TESTCASE(NewCase)
{
	/* Construct the tests case */
	int var = 1;

	/* Start testing */
	TEST(first_test)
	{ /* First TEST */
		var++;
		ASSERT(var == 2);
	}

	TEST(second_test)
	{
		/* A failed test */
		ASSERT(var == 2);
	}
}
ENDTESTCASE

TESTCASE(TestingTime)
{
#define N 1e6

	/* Take time */
	size_t sum = 0;
	for (size_t i = 0; i < N; i++)
		sum = 1;

	TEST(SumGreaterThanZero) { ASSERT(sum > 0); }
}
ENDTESTCASE

int main(void)
{
	/* Run the tests case */

	/* it is better to Catch it

	RUN(Testfoo);

	RUN(NewCase);
	*/

	// CATCH(Testfoo, NewCase, TestingMalloc);

	/*  Run the tree at once */
	MUTE_ACTIVE(true);

	/* A few simple asserts */
	/* after running it should know a few things  */
	assert(TestingMalloc.testcase != NULL);
	assert(TestingMalloc.name != NULL);
	assert(TestingMalloc.file != NULL);

	RUN(Testfoo, NewCase, TestingMalloc, TestingTime);

	/* One test failed */
	assert(unittest_ret == -1);

	/* after running it should know a few things  */
	assert(TestingMalloc.amount == 2);
	assert(TestingMalloc.info.number_failed_asserts == 0);

	assert(NewCase.amount == 2);
	assert(NewCase.info.number_failed_asserts == 1);
}
