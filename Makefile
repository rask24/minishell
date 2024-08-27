# Executable and archive files
NAME			= minishell
LIBFT			= $(LIBFT_DIR)/libft.a
LIBREADLINE		= $(LIBREADLINE_DIR)/lib/libreadline.a

# Compiler options
CFLAGS			= -Wall -Wextra -Werror
PROD_FLAGS		= -O3
DEV_FLAGS		= -O0 -g -fsanitize=address,undefined,integer
DEP_FLAGS		= -MMD -MP
INCLUDE			= -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR) -I $(LIBREADLINE_DIR)/$(INC_DIR)
LD_FLAGS		= -L $(LIBFT_DIR) -L $(LIBREADLINE_DIR)/lib
LD_LIBS			= -lft -lreadline -lncurses

# Directories
SRC_DIR			= src
BUILD_DIR		= build
INC_DIR			= include
LIBFT_DIR		= libft
LIBREADLINE_DIR	= readline

# Files
SRC				= $(SRC_DIR)/main.c \
					$(SRC_DIR)/token/constructor.c \
					$(SRC_DIR)/token/destructor.c \
					$(SRC_DIR)/token/getter.c  \

OBJ				= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))
DEP				= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.d, $(SRC))
HEADER			=

# Colors
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

# Rules
.PHONY: all
all: CFLAGS += $(PROD_FLAGS)
all: $(NAME)

$(NAME): $(LIBFT) $(LIBREADLINE) $(SRC) $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) $(LD_FLAGS) $(LD_LIBS) -o $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDE) $(DEP_FLAGS) -c $< -o $@

$(LIBFT):
	@git submodule update --init
	@make -C $(LIBFT_DIR)

$(LIBREADLINE):
	@git submodule update --init
	@cd readline \
	&& CC=cc ./configure --prefix=$(PWD)/readline --enable-shared=no --disable-install-examples \
	&& make -j \
	&& make -j install

-include $(DEP)

.PHONY: clean
clean:
	@-make clean -C $(LIBFT_DIR)
	@-make clean -C $(LIBREADLINE_DIR)
	$(RM) $(OBJ) $(DEP)

.PHONY: fclean
fclean: clean
	@-make fclean -C $(LIBFT_DIR)
	@-make uninstall -C $(LIBREADLINE_DIR)
	$(RM) $(NAME)

.PHONY: re
re: fclean all

.PHONY: norm
norm:
	norminette $(SRC_DIR) $(INC_DIR)

include unit_test.mk
include coverage.mk
