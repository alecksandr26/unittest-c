
#define TEST_DIR "dir4/"
#define TEST_OUT "testc.out"
#define UNITTEST_RECOMPILE 
#include "../include/unittest.h"

#include <stdio.h>


int main()
{



	INCLUDE_SUIT("simpletest.c", MySuit);

	RUN();
	return 0;
}
