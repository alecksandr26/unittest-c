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
	{ /* Second test */
		/* Do your assertions */
		ASSERT(var == 1);
	}
}
ENDTESTCASE

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

/* First suit */
NEW_SUIT(FirstSuit, Testfoo, NewCase);

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

NEW_SUIT(SecondSuit, TestingMalloc);

int main(void)
{
	/* RUN(FirstSuit, SecondSuit) */
	CATCH(FirstSuit, SecondSuit);
	/* Better */

	assert(unittest_head_tc != NULL);
	assert(strcmp(unittest_head_tc->name, "TestingMalloc") ==
	       0);				/* Because it is pointing to newcase */
	assert(unittest_head_tc->next != NULL); /* Because it points to Testfoo */
	
	MUTE_ACTIVE();

	RUN();

	/* Everything runs well */
	assert(unittest_ret == 0);

	/* Check that the suits were created correctly */
	assert(FirstSuit.amount == 2);
	assert(SecondSuit.amount == 1);
}
