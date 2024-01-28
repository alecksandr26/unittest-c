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
