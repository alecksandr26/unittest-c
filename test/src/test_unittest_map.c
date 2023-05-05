#include "../../include/unittest_map.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void test_are_unique()
{
	/* Check the unique */
	char name[] = "random data to be mapped";

	char *ptr  = (char *) unittest_map((const uint8_t *) name, strlen(name));
	char *ptr2 = (char *) unittest_map((const uint8_t *) name, strlen(name));

	assert(ptr == ptr2 && "Both things must be unique");

	/* Test free */
	unittest_map_free((const uint8_t *) ptr, strlen(ptr));
}

void test_not_map()
{
	/* Check the unique */
	char  name[]  = "random data to be mapped";
	char  name2[] = "Ranomd data not mapped";
	char *ptr     = (char *) unittest_map((const uint8_t *) name, strlen(name));

	char *ptr2 = (char *) unittest_map_find((const uint8_t *) name2, strlen(name2));

	assert(ptr2 == NULL && "It didn't map to nothing");

	unittest_map_free((const uint8_t *) ptr, strlen(ptr));
}

int main(void)
{
	test_are_unique();
	test_not_map();

	return 0;
}
