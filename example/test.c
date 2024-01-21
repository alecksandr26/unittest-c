#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* To reompile it self */

#define TEST_DIR "dir/"
#define UNITTEST_RECOMPILE
#include "../include/unittest.h"


/* To compile without recomiple:

   cc dir/simpletest.c -c
   cc test_test_directory.c simpletest.o ../../lib/libunittest.a -lexcept -o test

   Now alone
   cc test_test_directory.c ../../lib/libunittest.a -lexcept -o test
*/


int main(void)
{
	INCLUDE_SUIT("simpletest.c", SecondSuit);
	INCLUDE_TESTCASE("simpletest.c", NewCase);
	INCLUDE_TESTCASE("simpletest2.c", NewCase2);
	INCLUDE_SUIT("anothertest.c", SecondSuit2);

	RUN();

	return 0;
}
