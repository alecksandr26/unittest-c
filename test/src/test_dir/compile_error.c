
#include "../../../include/unittest.h"


TESTCASE(TestRecompile) {
	int var1 = 1, var2 = 2;
	
	TEST(SimpleTest) {
		ASSERT(var1 != var2, "Shold be true");
	}

}


SUIT(MySuit, TestRecompile);

