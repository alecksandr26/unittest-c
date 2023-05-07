#include <unittest.h>
#include <stdio.h>

#undef TEST_DIR
#define TEST_DIR "dir3/"


int main(void)
{
	#undef UNITTEST_RECOMPILE
	#define UNITTEST_RECOMPILE 1
	
	INCLUDE_TEST_CASE("simpletest.c", SimpleTest);
	INCLUDE_SUIT("simpletest.c", MySuit);
	
	RUN();
	return 0;
}
