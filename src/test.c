#include <stdio.h>
#include <string.h>
#include <assert.h>

#define UNSUPPOERTED_DTYPE "Unsupported data type"

#define datatypes_format(x) _Generic((x),				\
				     int:    "%i",			\
				     long:    "%li",			\
				     short:    "%hi",			\
				     unsigned:   "%u",			\
				     unsigned long:    "%lu",		\
				     unsigned short:   "%hu",		\
				     double: "%lf",			\
				     float: "%f",			\
				     char:   "%c",			\
				     default: UNSUPPOERTED_DTYPE	\
				     )

void capture_first_10_hex_vals(const char *memory, size_t size, char *hex_string, size_t bsize)
{
	assert(memory != NULL);
	assert(hex_string != NULL);
	assert(size > 0);
	assert(bsize >= 21);

	size_t count = size < 10 ? size : 10;  // Limit to the first 10 values
	
	// Convert each byte to hexadecimal and concatenate to the string
	for (size_t i = 0; i < count; ++i)
		snprintf(hex_string + (i * 2), bsize - (i * 2), "%02X", memory[i]);
	
	hex_string[count * 2] = '\0';  // Null-terminate the string
}

struct person {
	int age;
	char *name;
};

int main(void)
{
	/* int val1 = 1,  val2 = 2; */
	/* float val1 = 1,  val2 = 2; */
	/* unsigned int val1 = 1,  val2 = 2; */
	unsigned int val1 = 1,  val2 = 2;
	
	char *format_val1 = datatypes_format(val1);
	char *format_val2 = datatypes_format(val2);
	char output[100];
	
	memset(output, 0, 100);
	sprintf(output, "%s != %s", format_val1, format_val2);

	puts(output);
	printf(output, val1, val2);
	puts("");

	struct person p1 = {
		.age = 10,
		.name = "Panchito"
	};

	struct person p2 = {
		.age = 10,
		.name = "Panchito2"
	};

	char *format_p1 = datatypes_format(p1);
	char *format_p2 = datatypes_format(p2);

	memset(output, 0, 100);
	if (strcmp(format_p1, UNSUPPOERTED_DTYPE) == 0) {
		char hex_vals_val1[100];
		char hex_vals_val2[100];

		memset(hex_vals_val1, 0, 100);
		memset(hex_vals_val2, 0, 100);

		capture_first_10_hex_vals((char *) &p1, sizeof(struct person), hex_vals_val1, 21);
		capture_first_10_hex_vals((char *) &p2, sizeof(struct person), hex_vals_val2, 21);
		strcat(output, "%s... != %s...");
		printf(output, hex_vals_val1, hex_vals_val2);
		
	} else {
		sprintf(output, "%s != %s", format_p1, format_p2);
		puts(output);
		printf(output, p1, p2);
		puts("");
	}
	
	// Uncommenting the line below will trigger the default case.
	// printable_datatype("Hello, World!");

	return 0;
}
