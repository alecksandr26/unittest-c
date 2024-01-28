

/* To compile this exmaple run:
   cc simple_example.c -lunittest
*/

#include <unittest.h>

#include <math.h>
#include <malloc.h>


TESTCASE(TestCaseSimple) {
	TEST(TestSimple) {
		double x = sqrt(2.0);
		INFO_VAR(x);
		ASSERT_NEAR(x, 1.414, 1e-3, "Testing the sqrt of 2");
	}

	void *null_ptr, *non_void_ptr;
		
	null_ptr = NULL;
	non_void_ptr = malloc(100);
	
	TEST(TestVoidPtr) {
		ASSERT_EQ(null_ptr, non_void_ptr, "Cheking null ptr");
	}
	

	free(non_void_ptr);
	
} ENDTESTCASE


int main(void)
{
	RUN(TestCaseSimple);

	return unittest_ret;
}






