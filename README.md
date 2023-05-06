# Table Of Contents
* [Description](https://github.com/alecksandr26/unittest-c#Description)
* [How to install it?](https://github.com/alecksandr26/unittest-c#how-to-install-it)
	* [Using yay](https://github.com/alecksandr26/unittest-c#using-yay)
	* [Using make](https://github.com/alecksandr26/unittest-c#using-make)
* [Getting started](https://github.com/alecksandr26/unittest-c#getting-started)
	* [How to write Test Cases?](https://github.com/alecksandr26/unittest-c#how-to-write-test-cases)
		* [Another testcase example](https://github.com/alecksandr26/unittest-c#another-testcase-example)
	* [How to create Suit Tests?]()
* [References](https://github.com/alecksandr26/unittest-c#getting-started)
# Description
***unittest c*** is a fast and simple macro-based unit testing framework for C. It's inspired by the Python unittest module and designed to reduce 
boilerplate code. With macros and a built-in test runner, it's ideal for large test suites.
# How to install it?
## Using `yay`
1. First, ensure that you have the ***yay package manager installed***. You can install it [AUR(en)-yay](https://aur.archlinux.org/packages/yay).
2. Once ***yay is installed***, you can search for ***the unittest-c package*** by running the following command:
```
yay -Ss unittest-c
```
3. If the package is found, you can proceed to install it by running the following command:
```
yay -S unittest-c
```
4. If the package is not found, you may need to update your package list by running the following command:
```
yay -Syu
```
That's it! After completing these steps, ***unittest-c*** should be installed on your system and ready to use.

## Using `make`
1. Clone the ***unittest-c repository*** from ***GitHub*** using the following command:
```
git clone https://github.com/alecksandr26/unittest-c.git
```
2. Change into the ***unittest-c*** directory:
```
cd unittest-c
```
3. ***Compile*** the unittest-c framework using make:
```
make compile
```
4. ***Install unittest-c*** to your system by running:
```
sudo make install
```
This will copy the ***unittest-c*** executable to your system's default binary directory, which should be in your PATH. You may be prompted to enter your
password for authentication.
5. Optionally, run the test to verify that the installation was successful:
```
make example_test_installed
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
3. Inside the test case defined using the TESTCASE macro, you can write individual test functions using the TEST macro. Each test function should contain one or more assertions that check a specific aspect of the code being tested. Additionally, you can write a few lines of code in the TESTCASE scope to set up a boilerplate code for each individual test, such as initializing variables or creating test fixtures. This code will be executed before each test in the test case, allowing you to reuse common setup logic across multiple tests.
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
4. Use the ***RUN*** macro to run the tests inside the test case. In your ***main()*** function, call ***RUN*** and pass in ***the name of the test case*** as an argument:
```C
int main(void)
{
    RUN(MyTestCase);
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

6. To compile the code, you must use the following two flags: ***-lunittest -lexcept***. The ***-lexcept*** flag is required because ***unittest-c*** uses an exception library ***c-exceptions*** in
its source code. If you want to learn more about how to use ***exceptions*** in your C code, you can check out the 
[c-exceptions](https://github.com/alecksandr26/c-exceptions) library, which is used by ***unittest-c.***
```
cc mytestfile.c -lunittest -lexcept
```
Finally, the output of the program should look like this because it contains an assertion that causes the program to exit with a non-zero status:
```
[term] $ ./a.out
F
======================================================================================
FAIL:		MyTest		(MyTestCase.MyTest)
--------------------------------------------------------------------------------------
Traceback...
	File "shit.c", line 10, in MyTest
AssertionError:	 "var != 1",	"This assertion should fail"

--------------------------------------------------------------------------------------
Ran 1 test in 0.000032s

FAILED(failures=1)

[term] $
```
### Another testcase example
Here's another example of how you can use the unittest-c framework to write your own test cases:
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
    }

} ENDTESTCASE

int main(void)
{
    // Call RUN macro with the name of the test case to run the tests
    RUN(MyTests);

    return 0;
}
```
Then the output says that the tests were exectued well, there is no error detected.
```
[term]$ ./a.out
..
--------------------------------------------------------------------------------------
Ran 2 test in 0.000031s

Ok

[term]$
```
This output shows that ***unittest-c*** executed two tests without ***any errors***, and that all assertions passed.

# References
1. Wikipedia contributors. (2022a). Boilerplate code. Wikipedia. https://en.wikipedia.org/wiki/Boilerplate_code
2. Wikipedia contributors. (2023a). Test suite. Wikipedia. https://en.wikipedia.org/wiki/Test_suite
3. Python, R. (2023). Getting Started With Testing in Python. realpython.com. https://realpython.com/python-testing/
