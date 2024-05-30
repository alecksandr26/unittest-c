# For debuggin
.SUFFIXES:
%:: SCCS/s.%
%:: RCS/%
%:: RCS/%,v
%:: %,v
%:: s.%

define \n


endef

PKGNAME = unittest-c
C = cc
C_DEBUG_FLAGS = -ggdb -pedantic -Wall -fPIC
C_COMPILE_FLAGS = -O2 -DNDEBUG -fno-stack-protector -z execstack -no-pie -fPIC
C_FLAGS = $(C_DEBUG_FLAGS)
C_FLAGS_EXCEPT_LIB = -lexcept
C_FLAGS_WHOLE_ARCHIVE = -Wl,--whole-archive
C_FLAGS_NO_WHOLE_ARCHIVE = -Wl,--no-whole-archive
SHARED_LIB_FLAGS = -lunittest

N = nasm
N_DEBUG_FLAGS = -g -f elf64
N_COMPILE_FLAGS = -f elf64
N_FLAGS = $(N_DEBUG_FLAGS)

AR = ar cr
CF = clang-format -i

V = valgrind
V_FLAGS = --quiet

M = makepkg
M_FLAGS = -f --config .makepkg.conf --skipinteg --noextract

GCU = ssh://aur@aur.archlinux.org/unittest-c.git # git clone

# Direcotories
OBJ_DIR = obj
SRC_DIR = src
TEST_DIR = test
LIB_DIR = lib
EXAMPLE_DIR = example
INCLUDE_DIR = include
BUILD_DIR = build
UPLOAD_DIR = upload

TEST_SRC_DIR = $(addprefix $(TEST_DIR)/, src)
TEST_BIN_DIR = $(addprefix $(TEST_DIR)/, bin)

OBJS = $(addprefix $(OBJ_DIR)/, debug.o info.o tcase.o suit.o valgrind.o command.o compile.o tfile.o dir.o \
				hashdates.o rerun.o unittest.o stackjmp.o)

STATIC_LIBS = $(addprefix $(LIB_DIR)/, libunittest.a)
SHARED_LIBS = $(addprefix $(LIB_DIR)/, libunittest.so)

EXAMPLES = $(addprefix $(EXAMPLE_DIR)/, simple_example.out)

TESTS = $(addprefix $(TEST_BIN_DIR)/, 	test_running_testcase.out\
					test_create_suit.out\
					test_multiple_suits.out\
					test_assert.out\
					test_expect.out\
					test_compile.out\
					test_compile_fails.out\
					test_log.out\
					test_crashed_test.out\
					test_info.out)

.PHONY: all compile pkg  upload-aur examples
all: $(OBJS) $(STATIC_LIBS) $(SHARED_LIBS) $(TESTS) # $(EXAMPLES)

$(OBJ_DIR):
	@echo Creating: $@
	@mkdir -p $@

$(LIB_DIR):
	@echo Creating: $@
	@mkdir -p $@

$(TEST_BIN_DIR):
	@echo Creating: $@
	@mkdir -p $@

$(UPLOAD_DIR):
	@echo Creating: $@
	@mkdir -p $@

$(EXAMPLE_DIR):
	@echo Creating: $@
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo Compiling: $@
	@$(C) $(C_FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.asm | $(OBJ_DIR)
	@echo Compiling: $@
	@$(N) $(N_FLAGS) $< -o $@

# Creates the library
$(LIB_DIR)/%.a: $(OBJS) | $(LIB_DIR)
	@echo Archiving: $^ -o $@
	@$(AR) $@ $^
	@ranlib $@

$(LIB_DIR)/%.so: $(STATIC_LIBS) | $(LIB_DIR)
	@echo Archiving: $^ -o $@
	@$(C) -shared -o $@ $(C_FLAGS_WHOLE_ARCHIVE) $^ $(C_FLAGS_TRY_CATCH_LIB) $(C_FLAGS_NO_WHOLE_ARCHIVE)

# Trying to fetch the compiled directory
$(EXAMPLE_DIR)/%.out: $(EXAMPLE_DIR)/%.c $(SHARED_LIBS) | $(EXAMPLE_DIR)
	@echo Compiling: $< -o $@ 
	@$(C) $(C_FLAGS) -L./$(LIB_DIR) $< -o $@ $(SHARED_LIB_FLAGS)

example_%.out: $(EXAMPLE_DIR)/%.out
	@echo Running
	@export LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH && \
	./$<

examples: $(addprefix example_, $(notdir $(EXAMPLES)))

# Compile the tests
$(TEST_BIN_DIR)/test_%.out: $(TEST_SRC_DIR)/test_%.c $(SHARED_LIBS) | $(TEST_BIN_DIR)
	@echo Compiling: $< -o $@
	@$(C) $(C_FLAGS) -L./$(LIB_DIR) $< -o $@ $(SHARED_LIB_FLAGS) $(C_FLAGS_EXCEPT_LIB)

# To run some tests
test_%.out: $(TEST_BIN_DIR)/test_%.out
	@echo Running: $<
	@export LD_LIBRARY_PATH=$(LIB_DIR):$$LD_LIBRARY_PATH && \
	DEBUGINFOD_URLS="https://debuginfod.archlinux.org" $(V) $(V_FLAGS) ./$<
	@echo Passed

test: $(notdir $(TESTS))

clean: 
ifneq ("$(wildcard $(OBJ_DIR))", "")
	@echo Removing: $(OBJ_DIR) $(wildcard $(OBJ_DIR)/*.o)
	@rm -r -v $(OBJ_DIR)
endif

ifneq ("$(wildcard $(LIB_DIR))", "")
	@echo Removing: $(LIB_DIR) $(wildcard $(LIB_DIR)/*.a)
	@rm -r -v $(LIB_DIR)
endif

ifneq ("$(wildcard $(TEST_BIN_DIR))", "")
	@echo Removing: $(TEST_BIN_DIR) $(wildcard $(TEST_BIN_DIR)/*.out)
	@rm -r -v $(TEST_BIN_DIR)
endif

# Delete all build pacakge files
ifneq ("$(wildcard *.tar.zst)", "")
	@echo Removing: $(wildcard *.tar.zst)
	@rm $(wildcard *.tar.zst)
endif

ifneq ("$(wildcard *.tar.gz)", "")
	@echo Removing: $(wildcard *.tar.gz)
	@rm $(wildcard *.tar.gz)
endif

ifneq ("$(wildcard $(UPLOAD_DIR))", "")
	@echo Removing: $(UPLOAD_DIR)
	@rm -rf $(UPLOAD_DIR)
endif

# To format all the code
format: 
	@echo Formatting: $(wildcard $(SRC_DIR)/*.c)
	@$(CF) $(wildcard $(SRC_DIR)/*.c)
	@echo Formatting: $(wildcard $(INCLUDE_DIR)/*.h)
	@$(CF) $(wildcard $(INCLUDE_DIR)/*.h)
	@echo Formatting: $(wildcard $(TEST_SRC_DIR)/*.c)
	@$(CF) $(wildcard $(TEST_SRC_DIR)/*.c)
	@echo Formatting: $(wildcard $(EXAMPLE_DIR)/*.c)
	@$(CF) $(wildcard $(EXAMPLE_DIR)/*.c)

# Clean objects and libs and recompile with optimizations
compile: C_FLAGS = $(C_COMPILE_FLAGS)
compile: clean $(SHARED_LIBS)

pkg:
	@$(M) $(M_FLAGS)

$(UPLOAD_DIR)/$(PKGNAME): $(UPLOAD_DIR)
	@cd $< && git clone $(GCU)

upload-aur: $(UPLOAD_DIR)/$(PKGNAME)
	@cp PKGBUILD $</
	@cd $</ && $(M) --printsrcinfo > .SRCINFO
	@cd $</ && git add PKGBUILD .SRCINFO
	@echo -n "Commit-msg: "
	@read commitmsg
	@cd $</ && git commit -m commitmsg
	@cd $</ && git push
