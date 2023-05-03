#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "../../include/unittest.h"
#undef TEST_DIR
#define TEST_DIR "dir/"

/* To compile without recomiple:
   
   cc dir/simpletest.c -c
   cc test_test_directory.c simpletest.o ../../lib/libunittest.a -lexcept
*/

int main(void) 
{
	INCLUDE_SUIT("simpletest.c", SecondSuit);
	INCLUDE_TEST_CASE("simpletest.c", NewCase);

	RUN();
	return 0;
}




