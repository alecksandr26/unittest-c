

/* To compile this exmaple run:
   cc simple_example.c -lunittest && ./a.out
*/

#include <unittest.h>

#include <math.h>
#include <malloc.h>
#include <string.h>

TESTCASE(MyTestCase1) {
	TEST(TestSqrt2) {
		double x = sqrt(2.0);
		INFO_VAR(x);
		ASSERT_NEAR(x, 1.414, 1e-3, "Testing the sqrt of 2");
	}

	void *null_ptr, *non_null_ptr;
		
	null_ptr = NULL;
	non_null_ptr = malloc(100);
	
	TEST(TestingTheAssert_eq) {
		INFO("%p", null_ptr);
		INFO("%p", non_null_ptr);
		ASSERT_EQ(null_ptr, non_null_ptr, "Cheking null ptr");
	}

	free(non_null_ptr);
} ENDTESTCASE


TESTCASE(MyTestCase2) {

	struct Person {
		char name[100];
		int age;
	};
	
	TEST(TestingNonEq) {
		struct Person p1;
		memset(&p1, 0, sizeof(struct Person));
		p1.age = 10;
		strcpy(p1.name, "Pedrito");


		struct Person p2;
		memset(&p2, 0, sizeof(struct Person));
		p2.age = 10;
		strcpy(p2.name, "Pedrito");
		
		INFO_EXPR(strcmp(p1.name, p2.name));

		EXPECT_NEQ(p1, p2, "Should throw a warning");
	}
} ENDTESTCASE


SUIT(MySuit, MyTestCase1, MyTestCase2);

int main(void)
{
	RUN(MySuit);
	
	return unittest_ret;
}






