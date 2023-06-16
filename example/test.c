#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* To reompile it self */
#include "../include/unittest.h"

#undef TEST_DIR
#define TEST_DIR "dir/"

/* To compile without recomiple:

   cc dir/simpletest.c -c
   cc test_test_directory.c simpletest.o ../../lib/libunittest.a -lexcept -o test

   Now alone
   cc test_test_directory.c ../../lib/libunittest.a -lexcept -o test
*/

/* flags to start the automate recompilation mode */
#undef UNITTEST_RECOMPILE
#define UNITTEST_RECOMPILE 1

int main(void)
{
	INCLUDE_SUIT("simpletest.c", SecondSuit);
	INCLUDE_TEST_CASE("simpletest.c", NewCase);
	INCLUDE_TEST_CASE("simpletest2.c", NewCase2);
	INCLUDE_SUIT("anothertest.c", SecondSuit2);

	RUN();

	return 0;
}
