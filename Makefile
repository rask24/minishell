# Executable and archive files
NAME			= minishell
LIBFT			= $(LIBFT_DIR)/libft.a
LIBREADLINE		= $(LIBREADLINE_DIR)/lib/libreadline.a

# Compiler options
CFLAGS			= -Wall -Wextra -Werror
PROD_FLAGS		= -O3
DEV_FLAGS		= -O0 -g -fsanitize=address,undefined,integer
DEP_FLAGS		= -MMD -MP
INCLUDE			= -I$(INC_DIR) -I$(LIBFT_DIR)/$(INC_DIR) -I$(LIBREADLINE_DIR)/$(INC_DIR)
LD_FLAGS		= -L$(LIBFT_DIR) -L$(LIBREADLINE_DIR)/lib
LD_LIBS			= -lft -lreadline -lncurses

# Directories
SRC_DIR			= src
BUILD_DIR		= build
INC_DIR			= include
LIBFT_DIR		= libft
LIBREADLINE_DIR	= readline

# Files
SRC				= $(SRC_DIR)/main.c \
					$(SRC_DIR)/ast/constructor.c \
					$(SRC_DIR)/ast/convert_cmd_args_to_array.c \
					$(SRC_DIR)/ast/destructor.c \
					$(SRC_DIR)/ast/getter.c \
					$(SRC_DIR)/ast/push.c \
					$(SRC_DIR)/ast/setter.c \
					$(SRC_DIR)/builtins/builtins_cd.c \
					$(SRC_DIR)/builtins/builtins_cd_utils.c \
					$(SRC_DIR)/builtins/builtins_echo.c \
					$(SRC_DIR)/builtins/builtins_env.c \
					$(SRC_DIR)/builtins/builtins_exit.c \
					$(SRC_DIR)/builtins/builtins_export.c \
					$(SRC_DIR)/builtins/builtins_export_utils.c \
					$(SRC_DIR)/builtins/builtins_pwd.c \
					$(SRC_DIR)/builtins/builtins_unset.c \
					$(SRC_DIR)/exec/execute_and_or.c \
					$(SRC_DIR)/exec/execute_ast_node.c \
					$(SRC_DIR)/exec/execute_pipeline.c \
					$(SRC_DIR)/exec/execute_command.c \
					$(SRC_DIR)/exec/execute_subshell.c \
					$(SRC_DIR)/exec/handle_io.c \
					$(SRC_DIR)/exec/handle_redirect.c \
					$(SRC_DIR)/exec/open_heredoc.c \
					$(SRC_DIR)/exec/spawn_command.c \
					$(SRC_DIR)/exec/wait_children.c \
					$(SRC_DIR)/expansion/expand.c \
					$(SRC_DIR)/expansion/expand_quotes.c \
					$(SRC_DIR)/expansion/expand_quotes_on_list.c \
					$(SRC_DIR)/expansion/expand_variable_heredoc.c \
					$(SRC_DIR)/expansion/expand_variable_on_list.c \
					$(SRC_DIR)/expansion/expand_wildcard_on_list.c \
					$(SRC_DIR)/expansion/split_by_ifs.c \
					$(SRC_DIR)/expansion/normalize_list.c \
					$(SRC_DIR)/expansion/trim_expanded_variable.c \
					$(SRC_DIR)/expansion/wildcard_lazy_match.c \
					$(SRC_DIR)/env/constructor.c \
					$(SRC_DIR)/env/convert_env_to_array.c \
					$(SRC_DIR)/env/convert_array_to_env.c \
					$(SRC_DIR)/env/destructor.c \
					$(SRC_DIR)/env/getter.c \
					$(SRC_DIR)/env/init_env.c \
					$(SRC_DIR)/env/lookup.c \
					$(SRC_DIR)/env/update.c \
					$(SRC_DIR)/env/setter.c \
					$(SRC_DIR)/lexer/get_next_token.c \
					$(SRC_DIR)/lexer/is_start_of_input.c \
					$(SRC_DIR)/lexer/lexer.c \
					$(SRC_DIR)/lexer/process_blank.c \
					$(SRC_DIR)/lexer/process_comment.c \
					$(SRC_DIR)/lexer/process_eof.c \
					$(SRC_DIR)/lexer/process_operator.c \
					$(SRC_DIR)/lexer/process_quote.c \
					$(SRC_DIR)/lexer/process_word.c \
					$(SRC_DIR)/parser/create_heredoc.c \
					$(SRC_DIR)/parser/handle_heredoc.c \
					$(SRC_DIR)/parser/parse_command.c \
					$(SRC_DIR)/parser/parse_list.c \
					$(SRC_DIR)/parser/parse_simple_command.c \
					$(SRC_DIR)/parser/parse_pipeline.c \
					$(SRC_DIR)/parser/parser_utils.c \
					$(SRC_DIR)/parser/parser.c \
					$(SRC_DIR)/parser/try_parse_redirect.c \
					$(SRC_DIR)/routine/loop.c \
					$(SRC_DIR)/token/constructor.c \
					$(SRC_DIR)/token/destructor.c \
					$(SRC_DIR)/token/getter.c  \
					$(SRC_DIR)/ui/create_siglist.c \
					$(SRC_DIR)/ui/event_hook.c \
					$(SRC_DIR)/ui/signal_handler.c \
					$(SRC_DIR)/ui/termios.c \
					$(SRC_DIR)/utils/create_tmpfile.c \
					$(SRC_DIR)/utils/ft_lstinsert.c \
					$(SRC_DIR)/utils/ft_lstiterp.c \
					$(SRC_DIR)/utils/ft_lstremove.c \
					$(SRC_DIR)/utils/ft_lstremove_if.c \
					$(SRC_DIR)/utils/ft_lstsort.c \
					$(SRC_DIR)/utils/ft_xstrjoin2.c \
					$(SRC_DIR)/utils/is_identifier.c \
					$(SRC_DIR)/utils/is_ifs.c \
					$(SRC_DIR)/utils/print_error.c \
					$(SRC_DIR)/utils/string_struct.c \
					$(SRC_DIR)/utils/wrapper/ft_xitoa.c \
					$(SRC_DIR)/utils/wrapper/ft_xlstnew.c \
					$(SRC_DIR)/utils/wrapper/ft_xstrdup.c \
					$(SRC_DIR)/utils/wrapper/ft_xstrjoin.c \
					$(SRC_DIR)/utils/wrapper/ft_xstrndup.c

OBJ				= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))
DEP				= $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.d, $(SRC))

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
