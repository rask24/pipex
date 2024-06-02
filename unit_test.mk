# executable files
TEST_NAME		= unit_tester

# compilar options
CXXFLAGS		= -std=c++17 -Wall -Wextra -Werror
PROD_FLAGS		= -O3

# directories
TEST_DIR		= test/unit
GTEST_DIR		= test/unit/gtest
TEST_BUILD_DIR	= test/build

# mandatory source files
OBJ_EXCLUDE_MAIN= $(filter-out $(BUILD_DIR)/main.o, $(OBJ))

# test files
TEST_SRC		= $(TEST_DIR)/test_resolve_command_path.cpp \
					$(TEST_DIR)/test_parse_commnad.cpp \
					$(TEST_DIR)/test_tokenize_commnad.cpp
TEST_OBJ		= $(patsubst $(TEST_DIR)/%.cpp, $(TEST_BUILD_DIR)/%.o, $(TEST_SRC))
GTEST_SRC		= $(GTEST_DIR)/gtest_main.cc $(GTEST_DIR)/gtest-all.cc
GTEST_OBJ		= $(patsubst $(GTEST_DIR)/%.cc, $(TEST_BUILD_DIR)/%.o, $(GTEST_SRC))

# google test version: 1.14.0
GTEST_ARCHIVE	= v1.14.0.tar.gz
GTEST_REPO_URL	= https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
GTEST_SRC_DIR	= googletest-1.14.0
GTEST_FUSE_URL	= https://raw.githubusercontent.com/google/googletest/ec44c6c1675c25b9827aacd08c02433cccde7780/googletest/scripts/fuse_gtest_files.py
GTEST_FUSE		= fuse_gtest_files.py

# rules for test
.PHONY: test
test: all $(GTEST_OBJ) $(TEST_OBJ)
	@$(CXX) -L $(LIBFT_DIR) -lft -lpthread $(OBJ_EXCLUDE_MAIN) $(TEST_OBJ) $(GTEST_OBJ) -o $(TEST_NAME)
	@echo "\n$(BLUE)[gtest]\t\t./$(TEST_NAME)$(RESET)\t$(GREEN)compiled ✔$(RESET)"
	./$(TEST_NAME)

.PHONY: clean_test
clean_test:
	@$(RM) -r $(TEST_BUILD_DIR)
	@echo "$(BLUE)[gtest]\t\t./$(TEST_NAME)$(RESET)\t$(GREEN)deleted ✔$(RESET)"

.PHONY: re_test
re_test: clean_test test

$(TEST_BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -I $(TEST_DIR) $(INCLUDE) -c $< -o $@
	@printf "$(GREEN)─$(RESET)"

$(GTEST_OBJ): $(GTEST_DIR)
	@echo "$(BLUE)[gtest]\t\t./$(TEST_NAME)$(RESET)\t$(WHITE)compling...$(RESET)"
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -I $(TEST_DIR) $(INCLUDE) -c $(GTEST_DIR)/gtest-all.cc -o $(TEST_BUILD_DIR)/gtest-all.o
	@printf "$(GREEN)─$(RESET)"
	@$(CXX) $(CXXFLAGS) -I $(TEST_DIR) $(INCLUDE) -c $(GTEST_DIR)/gtest_main.cc -o $(TEST_BUILD_DIR)/gtest_main.o
	@printf "$(GREEN)─$(RESET)"

$(GTEST_DIR):
	@echo "fetching google test"
	@curl -#OL $(GTEST_REPO_URL)
	@echo "fetching fuse_gtest_files.py"
	@curl -#OL $(GTEST_FUSE_URL)
	@tar -xzf $(GTEST_ARCHIVE) $(GTEST_SRC_DIR)
	@python3 $(GTEST_FUSE) $(GTEST_SRC_DIR)/googletest $(GTEST_DIR)
	@mv $(GTEST_SRC_DIR)/googletest/src/gtest_main.cc $(GTEST_DIR)
	@mv $(GTEST_DIR)/gtest/* $(GTEST_DIR)
	@$(RM) -r $(GTEST_SRC_DIR) $(GTEST_DIR)/gtest $(GTEST_ARCHIVE) $(GTEST_FUSE)
