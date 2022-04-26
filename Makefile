CC = gcc
CFLAGS = -Wall -Wextra -Werror
SANITIZE = -fsanitize=address
NAME = minishell
LIBFT_DIR = libft
INCLUDES = -I/usr/local/opt/readline/include
HEADERS_LIST = libft.h
HEADERS_DIR = .
HEADERS = $(addprefix $(HEADERS_DIR), $(HEADERS_LIST))
SRCS = main.c parser_2.c commands.c commands_execute.c commands_file_input.c commands_file_output.c commands_find_path.c commands_utils.c buildin.c ft_echo.c ft_signal.c ft_cd.c ft_pwd.c ft_exit.c ft_unset.c ft_env.c ft_export.c ft_export_2.c ft_export_3.c arr.c term.c esc.c esc2.c history_list.c history.c parser.c utils.c open_quotes.c open_quotes_utils.c open_quotes_utils_2.c parser_utils.c term_for_here.c commands_file_input_2.c
TEST_SRCS = stat.c 
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

DEP_DIR := $(OBJ_DIR)/.deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.Td
COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS)
POSTCOMPILE = mv -f $(DEP_DIR)/$*.Td $(DEP_DIR)/$*.d && touch $@

LDFLAGS = -L$(LIBFT_DIR) -L. -L/usr/local/opt/readline/lib 
#-L /Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include
LDLIBS = -lft -lreadline -ltermcap #link libft library

 #search for library in ./ path

DEF = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
LYELLOW = \033[0;33m
YELLOW = \033[1;33m
BLUE = \033[1;34m
MAGENTA = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m

all:
		@$(MAKE) $(NAME)

$(NAME): $(OBJS)
		@echo "$(YELLOW)'$(NAME)' Object files were born!$(DEF)"
		@$(MAKE) -C $(LIBFT_DIR)/
		@$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^
		@echo "$(GREEN)Program '$@' is ready to be used.$(DEF)"

debug: $(NAME)
		@$(CC) $(LDFLAGS) $(LDLIBS) -o $(NAME) -gdwarf $(SRCS)
		@echo "$(WHITE)Debugging initiated.$(DEF)"

sanitize: $(NAME)
		@$(CC) $(LDFLAGS) $(LDLIBS) -o $(NAME) $(SANITIZE) $(SRCS)
		@echo "$(WHITE)Sanitizer initiated.$(DEF)"

test:
		@$(CC) $(LDFLAGS) $(LDLIBS) -gdwarf $(TEST_SRCS)

$(OBJ_DIR):
		@mkdir -p $@
		@echo "$(CYAN)Folder '$@' was created.$(DEF)"

$(OBJ_DIR)/%.o: %.c $(DEP_DIR)/%.d | $(DEP_DIR)
		@$(COMPILE.c) $(INCLUDES) -c $< -o $@
		@$(POSTCOMPILE)
		@echo "$(RED).$(DEF)\c"

$(DEP_DIR):
		@mkdir -p $@
		@echo "$(CYAN)Folder "$@" was created.$(DEF)"

DEPFILES = $(SRCS:%.c=$(DEP_DIR)/%.d)
$(DEPFILES):

cleandep:
		@rm -rf $(DEP_DIR)

clean:
		@rm -rf $(OBJ_DIR)
		@$(MAKE) clean -C $(LIBFT_DIR)/
		@echo "$(RED)Folder '$(OBJ_DIR)' and all files inside were deleted.$(DEF)"

cleandebug:
		@rm -rf $(NAME).dSYM
		@echo "$(MAGENTA)Debug files were deleted.$(DEF)"

fclean: clean
		@rm -f $(NAME)
		@$(MAKE) fclean -C $(LIBFT_DIR)
		@rm -f cub3D.bmp
		@echo "$(MAGENTA)Program '$(NAME)' was deleted.$(DEF)"

re: fclean all

include $(wildcard $(DEPFILES))

.PHONY: all clean fclean re bonus cleandep debug
