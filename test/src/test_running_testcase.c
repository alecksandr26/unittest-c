
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../include/unittest.h"

TestCase(TestingMalloc) {
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


/* Creates a new test */
TestCase(NewCase) {
	/* Construct the tests case */
	int var = 1;
	
	/* Start testing */
	Test(first_test) {	/* First Test */
		var++;
		assert(var == 2);
		printf("Isolated in %s: %i\n", test_case.current_test, var);
	}

	Test(second_test) { 	/* Second test */
		/* Do your assertions */
		assert(var == 1);
		printf("Isolated in %s: %i\n", test_case.current_test, var);
	}
} EndTestCase


int main()
{
	/* Run the tests */
	NewCase();
	
	TestingMalloc();
}

