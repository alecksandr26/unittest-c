# For debuggin
.SUFFIXES:
%:: SCCS/s.%
%:: RCS/%
%:: RCS/%,v
%:: %,v
%:: s.%

define \n


endef

C = cc
C_DEBUG_FLAGS = -ggdb -pedantic -Wall
C_COMPILE_FLAGS = -O2 -DNDEBUG -fno-stack-protector -z execstack -no-pie
C_FLAGS = $(C_DEBUG_FLAGS)
C_FLAGS_LIBS = -lexcept

AR = ar cr
CF = clang-format -i

V = valgrind
V_FLAGS = --leak-check=full --track-origins=yes -s  --show-leak-kinds=all

OBJ_DIR = obj
SRC_DIR = src
TEST_DIR = test
LIB_DIR = lib
INCLUDE_DIR = include
EXAMPLE_DIR = example

# For installation
INSTALL_LIB_DIR = /usr/lib
INSTALL_INCLUDE_DIR = /usr/include

TEST_SRC_DIR = $(addprefix $(TEST_DIR)/, src)
TEST_BIN_DIR = $(addprefix $(TEST_DIR)/, bin)

INTERFACES = $(addprefix $(INCLUDE_DIR)/, 	unittest_assert.h\
						unittest_exceptions.h\
						unittest.h\
						unittest_map.h\
						unittest_recompile.h\
						unittest_suit.h\
						unittest_tcase.h\
						unittest_tfile.h)

OBJS = $(addprefix $(OBJ_DIR)/, unittest.o \
				map.o \
				assert.o \
				tcase.o\
				suit.o\
				tfile.o\
				recompile.o)

LIBS = $(addprefix $(LIB_DIR)/, libunittest.a)
EXAMPLES = $(addprefix $(EXAMPLE_DIR)/, test.out \
					testc.out \
					valgrind_test.out)

TESTS = $(addprefix $(TEST_BIN_DIR)/, 	test_running_testcase.out \
					test_create_suit.out \
					test_multiple_suits.out\
					test_unittest_map.out\
					test_assert.out\
					test_recompile.out)

all: $(OBJ_DIR) $(LIB_DIR) $(TEST_BIN_DIR) $(OBJS) $(LIBS) $(TESTS) $(EXAMPLES)

$(OBJ_DIR):
	@echo Creating: $@
	@mkdir -p $@

$(LIB_DIR):
	@echo Creating: $@
	@mkdir -p $@

$(TEST_BIN_DIR):
	@echo Creating: $@
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo Compiling: $@
	@$(C) $(C_FLAGS) -c $< -o $@ $(C_FLAGS_LIBS)

# Creates the library
$(LIB_DIR)/%.a: $(OBJS) $(LIB_DIR)
	@echo Archiving: $@ $(filter-out $(LIB_DIR), $^)
	@$(AR) $@ $(filter-out $(LIB_DIR), $^)
	@ranlib $@

# Trying to fetch the compiled directory
$(EXAMPLE_DIR)/%.out: $(EXAMPLE_DIR)/%.c $(LIBS)
	@echo Compiling: $< -o $@ 
	@$(C) $(C_FLAGS) $< $(filter-out $<, $^) -o $@ $(C_FLAGS_LIBS)

example_%.out: $(EXAMPLE_DIR)/%.out
	@echo Running
	@./$<

example: $(addprefix example_, $(notdir $(EXAMPLES)))

# Compile the tests
$(TEST_BIN_DIR)/test_%.out: $(TEST_SRC_DIR)/test_%.c $(LIBS)
	@echo Compiling: $(filter-out $(TEST_BIN_DIR), $^) -o $@
	@$(C) $(C_FLAGS) $(filter-out $(TEST_BIN_DIR), $^) -o $@ $(C_FLAGS_LIBS)


# To run some tests
test_%.out: $(TEST_BIN_DIR)/test_%.out
	@echo Running: $<
	@$(V) $(V_FLAGS) ./$<
	@echo Passed

test: $(notdir $(TESTS))


clean_$(LIB_DIR)/%:
	@echo Removing: $(patsubst clean_%, %, $@)
	@rm $(patsubst clean_%, %, $@)

clean_$(OBJ_DIR)/%.o:
	@echo Removing: $(patsubst clean_%, %, $@)
	@rm $(patsubst clean_%, %, $@)

clean_$(TEST_BIN_DIR)/test_%.out:
	@echo Removing: $(patsubst clean_%, %, $@)
	@rm $(patsubst clean_%, %, $@)

clean:  $(addprefix clean_, $(wildcard $(LIB_DIR)/*.a)) \
	$(addprefix clean_, $(wildcard $(OBJ_DIR)/*.o)) \
	$(addprefix clean_, $(wildcard $(TEST_BIN_DIR)/*.out))
ifneq ("$(wildcard $(OBJ_DIR))", "")
	@echo Removing: $(OBJ_DIR)
	@rmdir $(OBJ_DIR)
endif

ifneq ("$(wildcard $(LIB_DIR))", "")
	@echo Removing: $(LIB_DIR)
	@rmdir $(LIB_DIR)
endif

ifneq ("$(wildcard $(TEST_BIN_DIR))", "")
	@echo Removing: $(TEST_BIN_DIR)
	@rmdir $(TEST_BIN_DIR)
endif


format_$(SRC_DIR)/%.c:
	@echo Formatting: $(patsubst format_%, %, $@)
	@$(CF) $(patsubst format_%, %, $@)

format_$(INCLUDE_DIR)/%.h:
	@echo Formatting: $(patsubst format_%, %, $@)
	@$(CF) $(patsubst format_%, %, $@)

format_$(TEST_SRC_DIR)/%.c:
	@echo Formatting: $(patsubst format_%, %, $@)
	@$(CF) $(patsubst format_%, %, $@)

format_$(EXAMPLE_DIR)/%.c:
	@echo Formatting: $(patsubst format_%, %, $@)
	@$(CF) $(patsubst format_%, %, $@)

# To format all the code
format: $(addprefix format_, 	$(wildcard $(SRC_DIR)/*.c) \
				$(wildcard $(INCLUDE_DIR)/*.h) \
				$(wildcard $(TEST_SRC_DIR)/*.c)\
				$(wildcard $(EXAMPLE_DIR)/*.c))

# Clean objects and libs and recompile with optimizations
compile: C_FLAGS = $(C_COMPILE_FLAGS)
compile: $(OBJ_DIR) $(LIB_DIR) $(TEST_BIN_DIR) \
	$(addprefix clean_, 	$(wildcard $(OBJ_DIR)/*.o) \
				$(wildcard $(LIB_DIR)/*.a) \
				$(wildcard $(TEST_BIN_DIR)/*.out)) \
	$(LIBS)

# Install header files
$(INSTALL_INCLUDE_DIR)/%.h: $(INCLUDE_DIR)/%.h
	@echo Installing: $< -o $@
	sudo install $< $@

$(INSTALL_LIB_DIR)/%.a: $(LIB_DIR)/%.a
	@echo Installing: $< -o $@
	sudo install $< $@

# Install the library
install: 	compile \
		$(addprefix $(INSTALL_INCLUDE_DIR)/, $(notdir $(INTERFACES)))\
		$(addprefix $(INSTALL_LIB_DIR)/, $(notdir $(LIBS)))
	@echo Installed:
