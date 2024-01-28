# Table Of Contents
* [Description](https://github.com/alecksandr26/unittest-c#Unit-Test-C)
* [License](https://github.com/alecksandr26/unittest-c#Unit-Test-C)
* [How to install it?](https://github.com/alecksandr26/unittest-c#how-to-install-it)
	* [Using yay](https://github.com/alecksandr26/unittest-c#using-yay)
	* [Using make](https://github.com/alecksandr26/unittest-c#using-make)
* [Getting started](https://github.com/alecksandr26/unittest-c#getting-started)
	* [How to write Test Cases?](https://github.com/alecksandr26/unittest-c#how-to-write-test-cases)
		* [Another example writting `Test Cases`](https://github.com/alecksandr26/unittest-c?tab=readme-ov-file#another-example-of-writing-test-cases)
		* [Log information](https://github.com/alecksandr26/unittest-c?tab=readme-ov-file#log-information)
  		* [How to Log information only on `Failure` or `Warning`?](https://github.com/alecksandr26/unittest-c?tab=readme-ov-file#how-to-log-information-only-on-failure-or-warning)
	* [How to create Suits?](https://github.com/alecksandr26/unittest-c#how-to-create-suits)
* [Assertions and Expectations](https://github.com/alecksandr26/unittest-c/?tab=readme-ov-file#assertions-and-expectations)
	* [Assertions Reference](https://github.com/alecksandr26/unittest-c/?tab=readme-ov-file#assertions-reference)
   	* [Expectations Reference](https://github.com/alecksandr26/unittest-c/?tab=readme-ov-file#expectations-reference)
* [How to include `Test Cases` and `Suits` from other files?](https://github.com/alecksandr26/unittest-c?tab=readme-ov-file#how-to-include-test-cases-and-suits-from-other-files)
	* [Including `Test Cases` and `Suits` manually](https://github.com/alecksandr26/unittest-c?tab=readme-ov-file#including-test-cases-and-suits-manually) 
	* [Automate the ***Compilation*** of the `Executable` and each individual `Test File`](https://github.com/alecksandr26/unittest-c?tab=readme-ov-file#automate-the-compilation-of-the-executable-and-each-individual-test-file)
   		* [ALERT!!!! Potential Bug in the Compilation Automation Feature](https://github.com/alecksandr26/unittest-c?tab=readme-ov-file#alert-potential-bug-in-the-compilation-automation-feature)
   		* [Attaching extra flags for the recompilation](https://github.com/alecksandr26/unittest-c#attaching-extra-flags-for-the-recompilation)
* [Incorporating ***Valgrind*** into the Test Execution Process](https://github.com/alecksandr26/unittest-c?tab=readme-ov-file#incorporating-valgrind-into-the-test-execution-process)
	* [Incorporating ***Valgrind*** manually]()
 	* [Incorporating ***Valgrind*** for the automated compilation process ]()
* [References](https://github.com/alecksandr26/unittest-c#references)
# Unit Test C
***Unit Test c*** is a fast and simple macro-based unit testing framework for C. It's inspired by the Python unittest module and designed to reduce 
boilerplate code. With macros and a built-in test runner, it's ideal for large test suites.
# How to install it?
## Using `yay`
1. First, ensure that you have the ***yay package manager*** installed. You can install it here: [install-and-use-yay-arch-linux](https://www.makeuseof.com/install-and-use-yay-arch-linux/).
2. Once ***yay is installed***, you can search for ***the unittest-c package*** by running the following command:
```bash
yay -Ss unittest-c
```
3. If the package is found, you can proceed to install it by running the following command:
```bash
yay -S unittest-c
```
4. If the package is not found, you may need to update your package list by running the following command:
```bash
yay -Syu
```
That's it! After completing these steps, ***unittest-c*** should be installed on your system and ready to use.

## Using `make`
1. Download one of the [releases](https://github.com/alecksandr26/unittest-c/releases) verions and unpack the code.
2. Change into the ***unittest-c*** directory:
```bash
cd unittest-c
```
3. ***Build the unittest-c package*** for your system by running:
```bash
make pkg
```
4. ***Install the package***, to install the framework into an ARCH system by running:
```bash
sudo pacman -U unittest-c-x.x.x-x-x86_64.pkg.tar.zst
```

That's it! After completing these five steps, unittest-c should be installed on your system and ready to use.
# Getting started
## How to write Test Cases?
1. Start by including the ***unittest.h*** header file in your C code:
```C
#include <unittest.h>
```
2. Define a test case using the ***TESTCASE macro***, which takes a name for the test case as an argument:
```C
TESTCASE(MyTestCase)
{
    // Tests code goes here
} ENDTESTCASE
```
3. Inside the test case defined using the TESTCASE macro, you can write individual test functions using the TEST macro. Each test function must contain the assertions and expectations that check a specific aspect of the code being tested. Additionally, you can write a few lines of code in the TESTCASE scope to set up a boilerplate code for each individual test, such as initializing variables or creating test fixtures. This code will be executed before each test in the test case, allowing you to reuse common setup logic across multiple tests.
```C
TESTCASE(MyTestCase)
{
    // the boilerplate code
    int var = 1;
    
    TEST(MyTest) {
        ASSERT(var == 1, "This assertion should pass");
        ASSERT(var != 1, "This assertion should fail");
    }
} ENDTESTCASE
```
To see all the avaiable assertions and expectations to been used follow this link: [Assertions and Expectations](https://github.com/alecksandr26/unittest-c/?tab=readme-ov-file#assertions-and-expectations)

4. Use the ***RUN*** macro to run the tests inside the test case. In your ***main()*** function, call ***RUN*** and pass in ***the name of the test case*** as an argument:
```C
int main(void)
{
    RUN(MyTestCase);
    return 0;
}
```
If you have several test cases in your file, you must pass them to the ***RUN*** macro as a list:
```c
int main(void)
{
    RUN(MyTestCase1, MyTestCase2, MyTestCase3, ...);
    return 0;
}
```

5. Here's a summary of what the final code might look like:
```C
#include <unittest.h>

TESTCASE(MyTestCase)
{
    // the boilerplate code
    int var = 1;
    
    TEST(MyTest) {
        ASSERT(var == 1, "This assertion should pass");
        ASSERT(var != 1, "This assertion should fail");
    }
} ENDTESTCASE


int main(void)
{
    RUN(MyTestCase);
    return 0;
}
```
6. To compile the code, you need to include the following flag: ***-lunittest***. This flag is necessary to dynamically link the ***unittest-c*** library.
```
cc mytestfile.c -lunittest
```
Finally, the output of the program should look like this because it contains an assertion that causes the program to exit with a non-zero status:
```
[term] $ ./a.out
F
======================================================================================
FAIL:		MyTest		(MyTestCase.MyTest)
--------------------------------------------------------------------------------------
Traceback...
	File "mytestfile.c", line 10, in MyTest
AssertionError:	 "var != 1",	"This assertion should fail"

--------------------------------------------------------------------------------------
Ran 1 test in 0.000032s

FAILED(failures=1)

[term] $
```
### Another example of writing `Test Cases`
Here's a more elaborate example of how you can use the unittest-c framework to write your own test cases:
```C
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

		EXPECT_NEQ(p1, p2, "Should throw a warning");
	}
} ENDTESTCASE

int main(void)
{
	RUN(MyTestCase1, MyTestCase2);

	return unittest_ret;
}
```
Then the output says that the tests were exectued well, there is an error and a warning detected.
```shell
[term]$ ./a.out
W.F
===========================================================================================
WARN:		TestingNonEq		(MyTestCase2.TestingNonEq)
-------------------------------------------------------------------------------------------
Traceback...
	File "simple_example.c", line 53, in TestingNonEq
ExpectationWarning:	 "p1 != p2, where p1 = 0X5065647269... and p2 = 0X5065647269... have unknown data types",
		 "Should throw a warning" 

===========================================================================================
FAIL:		TestingTheAssert_eq		(MyTestCase1.TestingTheAssert_eq)
-------------------------------------------------------------------------------------------
Traceback...
	File "simple_example.c", line 26, in TestingTheAssert_eq
AssertionError:	 "null_ptr == non_void_ptr, where null_ptr = (nil) and non_void_ptr = 0x65226f07a2a0",
		 "Cheking null ptr" 

-------------------------------------------------------------------------------------------
Ran 3 test in 0.002126s

FAILED(failures=1)

WARNED(warnings=1)


[term]$
```
This output shows that ***unittest-c*** executed three tests with an **assertion error** and an **expectation warning**.

### Log information
To facilitate logging information during the execution of a test case, the **LOG** macro can be employed. Building upon the code presented 
in the previous section, one can seamlessly integrate the **LOG** macro as follows:
```C
#include <unittest.h>

TESTCASE(MyTests)
{
    // Set up any boilerplate code for all tests in the test case
    int x = 42;

    // Define individual tests using the TEST macro
    TEST(Test1)
    {
        // Use ASSERT macro to check if x equals 42
        ASSERT(x == 42, "x should equal 42");
    }

    TEST(Test2)
    {
        // Use ASSERT macro to check if x is less than 100
        ASSERT(x < 100, "x should be less than 100");
	
	// Print the value of x using the LOG macro
        LOG("The value of x is: %i\n", x);
    }

} ENDTESTCASE

int main(void)
{
    // Call RUN macro with the name of the test case to run the tests
    RUN(MyTests);

    return 0;
}
```
With this modification, the output will now include the print statement with the value of `x`. An example of the updated output is provided below:
```shell
[term]$ ./a.out
.The value of x is: 42
.
--------------------------------------------------------------------------------------
Ran 2 test in 0.010490s

Ok 
```
### How to Log information only on `Failure` or `Warning`?
To log information specifically when a failure occurs during a test, the **INFO** macro can be utilized. The **INFO** macro allows you 
to print information during the runtime of a test, as it is essentially a wrapper for **sprintf**. By employing the following modification 
to one of the previous code examples, you can incorporate the **INFO** macro in tests where a failure is detected as follows:
```C
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

int main(void)
{
	RUN(MyTestCase1, MyTestCase2);

	return unittest_ret;
}
```
With this modification, the output will now include an info section for each testcase execution:
```shell
W.F
===========================================================================================
WARN:		TestingNonEq		(MyTestCase2.TestingNonEq)
-------------------------------------------------------------------------------------------
Traceback...
	File "simple_example.c", line 58, in TestingNonEq
ExpectationWarning:	 "p1 != p2, where p1 = 0X5065647269... and p2 = 0X5065647269... have unknown data types",
		 "Should throw a warning" 

===========================================================================================
INFO:		TestingNonEq		(MyTestCase2.TestingNonEq)
-------------------------------------------------------------------------------------------
	File "simple_example.c", line 56, in TestingNonEq
InformationMessage: "(strcmp(p1.name, p2.name)) ==> 0"

===========================================================================================
FAIL:		TestingTheAssert_eq		(MyTestCase1.TestingTheAssert_eq)
-------------------------------------------------------------------------------------------
Traceback...
	File "simple_example.c", line 29, in TestingTheAssert_eq
AssertionError:	 "null_ptr == non_null_ptr, where null_ptr = (nil) and non_null_ptr = 0x588f21e562a0",
		 "Cheking null ptr" 

===========================================================================================
INFO:		TestingTheAssert_eq		(MyTestCase1.TestingTheAssert_eq)
-------------------------------------------------------------------------------------------
	File "simple_example.c", line 27, in TestingTheAssert_eq
InformationMessage: "(nil)"

===========================================================================================
INFO:		TestingTheAssert_eq		(MyTestCase1.TestingTheAssert_eq)
-------------------------------------------------------------------------------------------
	File "simple_example.c", line 28, in TestingTheAssert_eq
InformationMessage: "0x588f21e562a0"

-------------------------------------------------------------------------------------------
Ran 3 test in 0.001498s

FAILED(failures=1)

WARNED(warnings=1)
```

## How to create `Suits`?
1. Create a new C file and include the ***unittest.h header*** at the beginning of your code.
```C
#include <unittest.h>
```
2. Define one or more test cases using the ***TESTCASE*** macro. Inside each test case, you can define individual tests using the ***TEST*** macro. 
   Use the ***ASSERT*** macro to check if a specific condition is true or false.
```C
TESTCASE(MyTestCases1)
{
    // Set up any boilerplate code for all tests in the test case
    int x = 42;

    // Define individual tests using the TEST macro
    TEST(Test1)
    {
        // Use ASSERT macro to check if x equals 42
        ASSERT(x == 42, "x should equal 42");
    }

    TEST(Test2)
    {
        // Use ASSERT macro to check if x is less than 100
        ASSERT(x < 100, "x should be less than 100");
    }

} ENDTESTCASE

TESTCASE(MyTestCases2)
{
    // Set up any boilerplate code for all tests in the test case
    int y = 100;

    // Define individual tests using the TEST macro
    TEST(Test3)
    {
        // Use ASSERT macro to check if y equals 100
        ASSERT(y == 100, "y should equal 100");
    }

    TEST(Test4)
    {
        // Use ASSERT macro to check if y is greater than or equal to 50
        ASSERT(y >= 50, "y should be greater than or equal to 50");
    }

} ENDTESTCASE
```
3. Create a new test suite using the ***SUIT*** macro, passing in the ***names*** of all the ***test cases*** you want to include in the suite as
 arguments.
```C
SUIT(MySuit, MyTestCases1, MyTestCases2);
```
4. In the ***main()*** function, call the RUN macro with ***the name of the test suite*** to run all the test cases.
```C
int main(void)
{
    // Call RUN macro with the name of the suit to run the test cases
    RUN(MySuit);

    return 0;
}
```
5. Compile the code with the ***flag mentioned in the previous section*** ([How to write Test Cases?](https://github.com/alecksandr26/unittest-c#how-to-write-test-cases)) and run the executable. You should see an output similar to this:
```shell
[term] $ cc mytestfile.c -lunittest
[term] $ ./a.out
....
--------------------------------------------------------------------------------------
Ran 4 test in 0.000015s

Ok

[term] $
```
Finally here is more elaborated example code from this section.
```C
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

// Create the suit
SUIT(MySuit, MyTestCase1, MyTestCase2);

int main(void)
{
	// Run the suit
	RUN(MySuit);
	
	return unittest_ret;
}
```
# Assertions and Expectations
This library offers **different assertions and expectations**. The difference between an assert and an expect is that an expect is a non-fatal assertion, which means it does not break a test; it only registers the failure information. In this library, expects are counted as simple warnings rather than failures because they are not fatal. Here are two lists of the available assertions and expectations.

## Assertions Reference
1. **ASSERT(EXPR, ...)**
   	- Evaluates the given expression and registers a failure if it is false.

2. **ASSERT_EQ(X, Y, ...)**
   	- Compares two variables for equality.

3. **ASSERT_NEQ(X, Y, ...)**
   	- Compares two variables for inequality.

4. **ASSERT_NEQ(X, Y, ...)**
   	- Checks if the first variable is less than the second.

5. **ASSERT_LE(X, Y, ...)**
  	- Checks if the first variable is less than or equal to the second.

6. **ASSERT_GT(X, Y, ...)**
   	- Checks if the first variable is greater than the second.

7. **ASSERT_GE(X, Y, ...)**
   	- Checks if the first variable is greater than or equal to the second.

8. **ASSERT_STR_EQ(X, Y, ...)**
   	- Compares two strings for equality.

9. **ASSERT_STR_NEQ(X, Y, ...)**
	- Compares two strings for inequality.

10. **ASSERT_NEAR(X, Y, abs_error, ...)**
   	- Asserts that the difference between two values does not exceed a specified absolute error.

11. **ASSERT_THROW(STATEMENT, EXCEPT, ...)**
   	- Verifies that a statement throws a specific exception.

12. **ASSERT_ANY_THROW(STATEMENT, ...)**
   	- Verifies that a statement throws an exception of any kind.

13. **ASSERT_NO_THROW(STATEMENT, ...)**
   	- Verifies that a statement does not throw any exception.
## Expectations Reference
1. **EXPECT(EXPR, ...)**
   	- Evaluates the given expression and registers a failure if it is false.

2. **EXPECT_EQ(X, Y, ...)**
   	- Compares two variables for equality.

3. **EXPECT_NEQ(X, Y, ...)**
   	- Compares two variables for inequality.

4. **EXPECT_NEQ(X, Y, ...)**
   	- Checks if the first variable is less than the second.

5. **EXPECT_LE(X, Y, ...)**
   	- Checks if the first variable is less than or equal to the second.

6. **EXPECT_GT(X, Y, ...)**
   	- Checks if the first variable is greater than the second.

7. **EXPECT_GE(X, Y, ...)**
   	- Checks if the first variable is greater than or equal to the second.

8. **EXPECT_STR_EQ(X, Y, ...)**
   	- Compares two strings for equality.

9. **EXPECT_STR_NEQ(X, Y, ...)**
   	- Compares two strings for inequality.

10. **EXPECT_NEAR(X, Y, abs_error, ...)**
	- Asserts that the difference between two values does not exceed a specified absolute error.

11. **EXPECT_THROW(STATEMENT, EXCEPT, ...)**
	- Verifies that a statement throws a specific exception.

12. **EXPECT_ANY_THROW(STATEMENT, ...)**
	- Verifies that a statement throws an exception of any kind.

13. **EXPECT_NO_THROW(STATEMENT, ...)**
	- Verifies that a statement does not throw any exception.
    
# How to include `Test Cases` and `Suits` from other files?
## Including `Test Cases` and `Suits` manually
1. For example, let's create some testcases and a suit in a file called ***simpletest.c***:
```C
// simpletest.c
#include <unittest.h>

TESTCASE(SimpleTest) {
    int var = 1;

    TEST(Test1) {
        ASSERT(var == 1, "It should be one");
    }

    TEST(Test2) {
        ASSERT(var > 0, "It should be greater than zero");
    }

    TEST(Test3) {
        ASSERT(var < 2, "It should be lesser than 2");
    }

    TEST(Test4) {
        ASSERT(var != 0, "It should not be zero");
    }
} ENDTESTCASE


TESTCASE(MyTestCases1)
{
    // Set up any boilerplate code for all tests in the test case
    int x = 42;

    // Define individual tests using the TEST macro
    TEST(Test1)
    {
        // Use ASSERT macro to check if x equals 42
        ASSERT(x == 42, "x should equal 42");
    }

    TEST(Test2)
    {
        // Use ASSERT macro to check if x is less than 100
        ASSERT(x < 100, "x should be less than 100");
    }

} ENDTESTCASE

TESTCASE(MyTestCases2)
{
    // Set up any boilerplate code for all tests in the test case
    int y = 100;

    // Define individual tests using the TEST macro
    TEST(Test3)
    {
        // Use ASSERT macro to check if y equals 100
        ASSERT(y == 100, "y should equal 100");
    }

    TEST(Test4)
    {
        // Use ASSERT macro to check if y is greater than or equal to 50
        ASSERT(y >= 50, "y should be greater than or equal to 50");
    }

} ENDTESTCASE

SUIT(MySuit, MyTestCases1, MyTestCases2);
````
2. Create a new file, e.g. ***testrunner.c***, which will serve as your main test runner. In this file, include the test cases and the suit from the 
file that you want to run. 
You can use the ***INCLUDE_TEST_CASE*** and ***INCLUDE_SUIT*** macros to do this. Also, make sure that the file path in the ***TEST_DIR*** macro 
matches the actual directory where 
your ***simpletest.c*** is located. Here's an example:
```C
#include <stdio.h>

#define TEST_DIR "dir/"
#include <unittest.h>

int main(void)
{
	// Include a testcase
	INCLUDE_TESTCASE("simpletest.c", SimpleTest);
	
	// Include a suit
	INCLUDE_SUIT("simpletest.c", MySuit);

	/* Run the selected testcases or suits */
	RUN(SimpleTest, MySuit);
	
	return unittest_ret;
}
```
3. To compile the ***testrunner*** and the included test case, use the following command:
```
[term] $ cc -o testrunner testrunner.c dir/simpletest.c -lunittest
```
The ***dir3/simpletest.c*** file is the test case that was included in the previous step using the ***INCLUDE_TEST_CASE*** macro and here its output.
```shell
[term] $ ./testrunner
........
-------------------------------------------------------------------------------------------
Ran 8 test in 0.002476s

Ok 
```
4. Since the source code for unit tests are essentially code themselves, it's common to use build automation tools such as make or `cmake` or `make` 
to simplify 
the process of compiling and executing large test suites. These tools can create object files (.o) from your test source files, which can be 
linked together to create the final executable, heres is an example with a makefile.
```Makefile
C = cc
CFLAGS = -Wall -Werror
LDFLAGS = -lunittest
TEST_DIR = dir
TEST_OBJECTS = $(addprefix  $(TEST_DIR)/, simpletest.o)

all: testrunner

testrunner: $(TEST_OBJECTS) testrunner.o
	$(C) $(LDFLAGS) $(TEST_OBJECTS) testrunner.o -o testrunner

$(TEST_DIR)/simpletest.o: $(TEST_DIR)/simpletest.c
	$(C) $(CFLAGS) -c $(TEST_DIR)/simpletest.c -o $(TEST_DIR)/simpletest.o

testrunner.o: testrunner.c
	$(C) $(CFLAGS) -c testrunner.c -o testrunner.o

# Clean all the compiled things
clean:
	rm -f $(TEST_OBJECTS) testrunner.o testrunner

# To run the tests
test: testrunner
	./testrunner
```
And this is the output running the tests throughout `Makefile`.
```shell
[term] $ make test
cc -Wall -Werror -c dir/simpletest.c -o dir/simpletest.o
cc -Wall -Werror -c testrunner.c -o testrunner.o
cc -lunittest dir/simpletest.o testrunner.o -o testrunner
./testrunner
........
-------------------------------------------------------------------------------------------
Ran 8 test in 0.001662s

Ok 
```

## Automate the ***Compilation*** of the `Executable` and Each Individual `Test File`
1. To automate the compilation process using the framework, define the macro ***UNITTEST_RECOMPILE*** within your test runner or main test executable file.
   This can be achieved by adding the line ***#define UNITTEST_RECOMPILE*** before including the framework header file.
```C
#include <stdio.h>

#define TEST_DIR "dir/"
#define UNITTEST_RECOMPILE

#include <unittest.h>

int main(void)
{
	// Include a testcase
	INCLUDE_TESTCASE("simpletest.c", SimpleTest);
	
	// Include a suit
	INCLUDE_SUIT("simpletest.c", MySuit);

	/* Run the selected testcases or suits */
	RUN(SimpleTest, MySuit);
	
	return unittest_ret;
}
```
2. In the second step, you need to compile the test executable without ***any testfile source code***. 
This means that you need to exclude the source code files of your test cases, which were previously included in the compilation command in the previous section.
For example, if your test cases were included in the compilation command as follows:
```shell
[term] $ cc -o testrunner testrunner.c simpletest.c -lunittest
```
3. When you run the test executable, you will see a message indicating that the test files are being compiled, generating the .o files. After this compilation process, the tests will be executed as usual.
```shell
[term] $ ./testrunner
[COMPILING]:	dir/simpletest.c -o dir/.obj/simpletest.o
[LINKING]:	testrunner.c dir/.obj/simpletest.o  -o testrunner
........
-------------------------------------------------------------------------------------------
Ran 8 test in 0.003770s

Ok 

```
This automated compiled feature allows you to focus solely on writing new code and its tests, instead of worrying about compiling your large code tests. The framework creates an ***.obj*** directory where it stores the ***.o*** files, and it will automatically recompile the test files when it detects a change, making the process of compilation and writing tests more efficient.

### ALERT!!!! Potential Bug in the Compilation Automation Feature
There is a potential bug associated with the compilation automation feature. Specifically, this bug may occur if you update the header files of the code you wish to test but do not modify the corresponding test files. In such cases, the tests might execute using a previous version of the header files, resulting in unexpected bugs during test execution.
To mitigate this issue, it is recommended to delete the `DATE_HASHED_FILE(.date_hashed.bin)` file located within your `TEST_DIR` each time you make changes to your header files.


### Attaching extra flags for the compile automatitation
If you intend to use a third-partylibrary in your tests or if you wish to test a library or component, you might want to include it in the compilation process. To achieve this, follow the steps below:
1. Confirm that you have enabled the **recompile mode** feature in your code:
```C
#define UNITTEST_RECOMPILE
```
2. Inide your **main()** test runner binary, use the **ATTACH_EXTRA_LINKING_FLAGS(flags)** macro or **ATTACH_EXTRA_COMPILE_FLAGS(flags)**, providing the path to the component you want to test or the flag you want to include in the compilation process:
```C
#include <stdio.h>

#define TEST_DIR "dir/"
#define UNITTEST_RECOMPILE
#include <unittest.h>

int main(void)
{
	INCLUDE_TESTCASE("simpletest.c", SimpleTest);
	INCLUDE_SUIT("simpletest.c", MySuit);

	/* Include the testcase that tests foo */
	INCLUDE_TESTCASE("test_foo.c", TestingFoo);

	// Attaching compile flag
	ATTACH_EXTRA_COMPILE_FLAGS("-DTESTING");
	
	// Attaching obj/foo.o as an additional component for testing purposes
	ATTACH_EXTRA_LINKING_FLAGS("obj/foo.o");

	/* Run the selected testcases or suits */
	RUN(SimpleTest, MySuit);
	
	return unittest_ret;
}
```
Within the `test_foo.c` file, the testing of the foo component is performed. In this scenario, the foo function is designed to return the constant value `1`.
```C
/* Simple example to test the foo  */

#include <unittest.h>

TESTCASE(TestingFoo) {

	extern int foo(void);
	
	TEST(FooReturn1) {
		ASSERT_EQ(foo(), 1, "foo must to return 1");
	}
	
} ENDTESTCASE
```
3. In the code above, if you are trying to link object files for testing, it's important to consider the path where the file is located relative to the test runner. It's recommended to place the test runner at the root path of the project directory. In this example, the obj/foo.o file is attached for testing, assuming it is located in the project root directory. Adjust the path accordingly based on your project structure, for example look this structure.
```shell
[term] $ tree
.
├── dir
│   ├── simpletest.c
│   └── test_foo.c
├── obj
│   ├── foo.c
│   └── foo.o
├── testrunner
└── testrunner.c
2 directories, 6 files
```
4. In the code above, after taking care of the paths and setting up the necessary test suites and test cases, you can run the test runner as you normally do. When executing the test runner, you should expect an output similar to the following:
```shell
[term] $ cc -o testrunner testrunner.c simpletest.c -lunittest
[term] $ ./testrunner
[COMPILING]:	dir/test_foo.c -o dir/.obj/test_foo.o
[LINKING]:	testrunner.c dir/.obj/simpletest.o  -o testrunner
.........
-------------------------------------------------------------------------------------------
Ran 9 test in 0.003532s

Ok
```
# Incorporating ***Valgrind*** into the Test Execution Process
## Incorporating ***Valgrind*** manually
Incorporating Valgrind into the test execution process is a straightforward task when done manually. Simply execute the following command in the terminal:
```shell
[term] $ valgrind --quiet ./testrunner
........
-------------------------------------------------------------------------------------------
Ran 8 test in 0.131442s

Ok 

```
Considering that all memory utilized by the framework is statically allocated, Valgrind is expected to identify any allocations and memory leaks introduced by the tested code. It is advisable to use 
the `--quiet` flag, particularly since the framework forks the process for each individual test case. 
This precaution helps manage the potentially extensive log information that Valgrind may generate.
## Incorporating ***Valgrind*** for the automated compilation process 
1. Confirm that you have enabled the **recompile mode** feature in your code:
```C
#undef UNITTEST_RECOMPILE
#define UNITTEST_RECOMPILE 1
```
2. Within your **main()** test runner binary, invoke the **ACTIVE_VALGRIND()** macro to enable the valgrind feature.
```C
#undef TEST_DIR
#define TEST_DIR "dir3/"

int main(void)
{
	#undef UNITTEST_RECOMPILE
	#define UNITTEST_RECOMPILE 1
	
	INCLUDE_TEST_CASE("simpletest.c", SimpleTest);
	INCLUDE_SUIT("simpletest.c", MySuit);
	
	// Activate Valgrind for memory leak detection
	ACTIVE_VALGRIND();
	
	RUN();
	return 0;
}
```
Then, depending on the number of test cases present in **simpletest.c**, the output of this code will display something like the following:
```shell
[term] $ ./test
==10498== Memcheck, a memory error detector
==10498== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==10498== Using Valgrind-3.21.0 and LibVEX; rerun with -h for copyright info
==10498== Command: ./example/valgrind_test.out
==10498== 
.....
--------------------------------------------------------------------------------------
Ran 5 test in 0.008277s

Ok 

==10498== 
==10498== HEAP SUMMARY:
==10498==     in use at exit: 0 bytes in 0 blocks
==10498==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==10498== 
==10498== All heap blocks were freed -- no leaks are possible
==10498== 
==10498== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
# References
1. Wikipedia contributors. (2022a). Boilerplate code. Wikipedia. https://en.wikipedia.org/wiki/Boilerplate_code
2. Wikipedia contributors. (2023a). Test suite. Wikipedia. https://en.wikipedia.org/wiki/Test_suite
3. Python, R. (2023). Getting Started With Testing in Python. realpython.com. https://realpython.com/python-testing/
