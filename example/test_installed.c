
/* Testing the installed framework  */

#include <unittest.h>

/* To compile run like this
   cc test_installed.c -lunittest -lexcept -o test
 */

#undef TEST_DIR
#define TEST_DIR "dir2/"

int main()
{
#undef UNITTEST_RECOMPILE
#define UNITTEST_RECOMPILE 1

	INCLUDE_SUIT("anothertest.c", SecondSuit2);

	RUN();
	return 0;
}
