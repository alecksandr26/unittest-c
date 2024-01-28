

#include "../../../include/unittest.h"


TESTCASE(CrashTest) {
	void *ptr = NULL;

	struct person {
		char name[200];
		int age;
	};
	
	TEST(SimpleTest) {

		
		/* Crash here */
		struct person p = *((struct person *) ptr);

		ASSERT(p.age == 10, "Shold not be executed");
	}

} ENDTESTCASE


TESTCASE(NotCrashTest) {
	void *ptr = NULL;
	

	TEST(SimpleTest) {
		ASSERT(ptr == NULL, "Shold not be executed");
	}

} ENDTESTCASE


SUIT(CrashableSuit, CrashTest, NotCrashTest);




