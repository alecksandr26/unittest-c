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

N = nasm
N_DEBUG_FLAGS = -g -f elf64
N_COMPILE_FLAGS = -f elf64
N_FLAGS = $(N_DEBUG_FLAGS)

AR = ar rc
CF = clang-format -i

V = valgrind
V_FLAGS = --leak-check=full --track-origins=yes -s  --show-leak-kinds=all

OBJ_DIR = obj
SRC_DIR = src
TEST_DIR = test
LIB_DIR = lib
INCLUDE_DIR = include

TEST_SRC_DIR = $(addprefix $(TEST_DIR)/, src)
TEST_BIN_DIR = $(addprefix $(TEST_DIR)/, bin)

OBJS = $(addprefix $(OBJ_DIR)/, unittest.o)
LIBS = $(addprefix $(LIB_DIR)/, libunittest.a)

TESTS = $(addprefix $(TEST_BIN_DIR)/, test_running_testcase.out)

.PHONY: clean format
all: $(OBJ_DIR) $(LIB_DIR) $(TEST_BIN_DIR) $(OBJS) $(LIBS) $(TESTS)

$(OBJ_DIR):
	@echo Creating: $@
	@mkdir -p $@

$(LIB_DIR):
	@echo Creating: $@
	@mkdir -p $@

$(TEST_BIN_DIR):
	@echo Creating: $@
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	@echo Compiling: $@
	@$(C) $(C_FLAGS) -c $< -o $@ $(C_FLAGS_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm $(OBJ_DIR)
	@echo Compiling: $@
	@$(N) $(N_FLAGS) $< -o $@

# Compile the tests
$(TEST_BIN_DIR)/test_%.out: $(TEST_SRC_DIR)/test_%.c $(LIBS)
	@echo Compiling: $^ -o $@
	@$(C) $(C_FLAGS) $^ -o $@ $(C_FLAGS_LIBS)

# Creates the library
$(LIB_DIR)/%.a: $(OBJS)
	@echo Archiving: $@
	@$(AR) $@ $^
	@ranlib $@

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


# To format all the code
format: $(addprefix format_, 	$(wildcard $(SRC_DIR)/*.c) \
				$(wildcard $(INCLUDE_DIR)/*.h) \
				$(wildcard $(TEST_SRC_DIR)/*.c))

# To run some tests
test_%.out: $(TEST_BIN_DIR)/test_%.out
	@echo Running: $<
	@$(V) $(V_FLAGS) ./$<
	@echo Passed

test: $(notdir $(TESTS))

