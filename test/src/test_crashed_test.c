
#include "../../include/unittest.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct Student {
	char *name;
	int   age;
};

TESTCASE(Crashing)
{
	struct Student *s = NULL;

	TEST(NotCrashingTest)
	{
		/* Not Craching test */
		ASSERT(s == NULL);
		// LOG("Before crashing : (!!!!\n");
	}

	TEST(CrashingTest)
	{
		/* Crashing the testcase */
		printf("His mame: %s\n", s->name);
	}

	TEST(NotCrashingTest)
	{
		/* Not Craching test */
		ASSERT(s == NULL);
		// LOG("After crashing : (!!!!\n");
	}
}
ENDTESTCASE

TESTCASE(NotCrashing)
{
	struct Student *s = NULL;

	TEST(NotCrashingTest)
	{
		/* Not Craching test */
		ASSERT(s == NULL);
	}

	TEST(NotCrashingTest2)
	{
		/* Not Craching test */
		ASSERT(s == NULL);
	}
}
ENDTESTCASE

TESTCASE(NotCrashing2)
{
	struct Student *s = NULL;

	TEST(NotCrashingTest)
	{
		/* Not Craching test */
		ASSERT(s == NULL);
	}

	TEST(NotCrashingTest2)
	{
		/* Not Craching test */
		ASSERT(s == NULL);
	}
}
ENDTESTCASE

TESTCASE(ExitFailure)
{
	struct Student *s = NULL;

	TEST(ExitingWithFailure)
	{
		ASSERT(s == NULL);
		exit(EXIT_FAILURE);
	}
}
ENDTESTCASE

int main(void)
{
	MUTE_ACTIVE(true);

	RUN(NotCrashing2, Crashing, NotCrashing, ExitFailure);

	return 0;
}
