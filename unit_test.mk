# Main target
TEST_NAME			= unit_tester

# Compiler and flags
CXXFLAGS			= -std=c++17 -Wall -Wextra -Werror

# Directories
TEST_DIR			= tests/unit
GTEST_DIR			= googletest
TEST_BUILD_DIR		= build/tests

# Google Test settings
GTEST_VERSION		= 1.15.0
GTEST_URL			= https://github.com/google/googletest/archive/refs/tags/v$(GTEST_VERSION).tar.gz

# Source files
TEST_SRC			= $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ			= $(patsubst $(TEST_DIR)/%.cpp, $(TEST_BUILD_DIR)/%.o, $(TEST_SRC))
TEST_DEP			= $(patsubst $(TEST_DIR)/%.cpp, $(TEST_BUILD_DIR)/%.d, $(TEST_SRC))

# Exclude main from test object files
OBJ_EXCLUDE_MAIN	= $(filter-out $(BUILD_DIR)/main.o,$(OBJ))

# Google Test build marker
GTEST_MARKER		= $(GTEST_DIR)/.built

# Main test rule
.PHONY: test
test: all $(TEST_NAME)
	@echo "Running tests..."
	@./$(TEST_NAME)

# Build the test executable
$(TEST_NAME): $(GTEST_MARKER) $(TEST_OBJ) $(OBJ_EXCLUDE_MAIN)
	@echo "Linking $@..."
	@$(CXX) $(CXXFLAGS) $(TEST_OBJ) $(OBJ_EXCLUDE_MAIN) -o $@ -L$(GTEST_DIR)/lib $(LD_FLAGS) $(LD_LIBS) -lgtest -lgtest_main -lpthread

-include $(TEST_DEP)

# Compile test source files
$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(INCLUDE) $(DEP_FLAGS) -I$(GTEST_DIR)/googletest/include -I$(SRC_DIR) -c $< -o $@

# Build Google Test
$(GTEST_MARKER): $(GTEST_DIR)/CMakeLists.txt
	@echo "Building Google Test..."
	@cd $(GTEST_DIR) && cmake -DCMAKE_CXX_FLAGS=-std=c++17 . && make
	@touch $@

$(GTEST_DIR)/CMakeLists.txt:
	@echo "Downloading Google Test..."
	@mkdir -p $(GTEST_DIR)
	@curl -L $(GTEST_URL) | tar xz -C $(GTEST_DIR) --strip-components=1

# Clean test files
.PHONY: clean_test
clean_test:
	@echo "Cleaning test files..."
	@$(RM) -r $(TEST_BUILD_DIR) $(TEST_NAME) $(GTEST_DIR)

# Full rebuild of tests
.PHONY: re_test
re_test: clean_test test
