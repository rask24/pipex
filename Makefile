# executable and archive files
NAME		= pipex
LIBFT		= $(LIBFT_DIR)/libft.a

# compiler options
CFLAGS		= -Wall -Wextra -Werror
PROD_FLAGS	= -O3
DEV_FLAGS	= -O0 -g -fsanitize=address,undefined,integer
DEP_FLAGS	= -MMD -MP
INCLUDE		= -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR)
LD_FLAGS	= -L $(LIBFT_DIR)
LD_LIBS		= -lft

# directories
SRC_DIR		= src
BUILD_DIR	= build
INC_DIR		= include
LIBFT_DIR	= libft

# files
SRC			= $(SRC_DIR)/main.c \
				$(SRC_DIR)/exec/exec_command.c \
				$(SRC_DIR)/exec/resolve_command_path.c \
				$(SRC_DIR)/process/exec_all_processes.c \
				$(SRC_DIR)/process/exec_single_process.c \
				$(SRC_DIR)/process/init_processes.c \
				$(SRC_DIR)/split_word/split_word.c \
				$(SRC_DIR)/split_word/get_content.c \
				$(SRC_DIR)/split_word/create_word_list.c \
				$(SRC_DIR)/wrapper/ft_xsplit.c \
				$(SRC_DIR)/wrapper/ft_xstrjoin.c \
				$(SRC_DIR)/wrapper/xopen.c \
				$(SRC_DIR)/wrapper/xopen_with_permission.c \
				$(SRC_DIR)/wrapper/xclose.c \
				$(SRC_DIR)/wrapper/xpipe.c \
				$(SRC_DIR)/wrapper/xdup2.c \
				$(SRC_DIR)/wrapper/xfork.c \
				$(SRC_DIR)/wrapper/xunlink.c \
				$(SRC_DIR)/utils/error_exit.c
OBJ			= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))
DEP			= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.d, $(SRC))
HEADER		= $(wildcard $(INC_DIR)/*.h)

# colors
RESET			= \033[0m
ORANGE			= \033[0;33m
GRAY			= \033[0;90m
RED				= \033[0;91m
GREEN			= \033[1;92m
YELLOW			= \033[1;93m
BLUE			= \033[0;94m
MAGENTA			= \033[0;95m
CYAN			= \033[0;96m
WHITE			= \033[0;97m

# rules
.PHONY: all
all: CFLAGS += $(PROD_FLAGS)
all: $(NAME)

$(NAME): $(LIBFT) $(SRC) $(HEADER)
	@make _main CFLAGS="$(CFLAGS)"

.PHONY: _main
_main:
	@echo "$(BLUE)[$(NAME)]\t\t./$(NAME)$(RESET)\t\t$(WHITE)compling...$(RESET)"
	@make _build CFLAGS="$(CFLAGS)"

.PHONY: _build
_build: $(OBJ)
	@$(CC) $(CFLAGS) $^ $(LD_FLAGS) $(LD_LIBS) -o $(NAME)
	@echo "\n$(BLUE)[$(NAME)]\t\t./$(NAME)$(RESET)\t\t$(GREEN)compiled ✔$(RESET)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDE) $(DEP_FLAGS) -c $< -o $@
	@printf "$(GREEN)─$(RESET)"

$(LIBFT):
	git submodule update --init
	make -C $(LIBFT_DIR)

-include $(DEP)

.PHONY: clean
clean:
	@make clean -C $(LIBFT_DIR)
	@$(RM) $(OBJ) $(DEP)
	@echo "$(BLUE)[$(NAME)]\t\tobject files$(RESET)\t$(GREEN)deleted ✔$(RESET)"

.PHONY: fclean
fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)
	@echo "$(BLUE)[$(NAME)]\t\t./$(NAME)$(RESET)\t\t$(GREEN)deleted ✔$(RESET)"

.PHONY: re
re: fclean all

.PHONY: norm
norm:
	norminette $(SRC_DIR) $(INC_DIR)

include unit_test.mk
