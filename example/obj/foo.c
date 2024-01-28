
#include <string.h>
#include <malloc.h>

/* Foo function */

int x;

int foo(void)
{
	void *ptr = malloc(sizeof(x));
	
	return 1;
}


