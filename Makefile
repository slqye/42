################################################################################
#                                     CONFIG                                   #
################################################################################

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

LIBFT = sources/libft
SRCS_FILES =	main.c \
				utils.c \
				prompt/prompt.c \
				lexer/lexer.c \
				lexer/lexer_utils.c \
				lexer/hashmap.c \
				lexer/hashmap_utils.c \
				lexer/hashmap_quotes.c \
				lexer/hashmap_tokens.c \
				lexer/lexer_formater.c \
				lexer/lexer_geter.c \
				lexer/lexer_formater_utils.c \
				lexer/lexer_formater_quotes.c \
				lexer/lexer_expender.c \
				lexer/lexer_expender_utils.c \
				lexer/lexer_expender_ascii.c \
				parser/ast.c \
				parser/tree.c \
				parser/node.c \
				parser/prefix.c \
				parser/suffix.c \
				parser/redirect.c \
				parser/syntax.c \
				interpreter/interpreter.c \
				interpreter/interpreter_utils.c \
				interpreter/command.c \
				interpreter/command_utils.c \
				interpreter/f_pipe.c \
				interpreter/heredoc.c \
				interpreter/redirection.c \
				interpreter/safe_print.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c \
				interpreter/redirection_utils.c \
				interpreter/f_pipe_utils.c \
				builtins/builtins.c \
				builtins/echo.c \
				builtins/pwd.c \
				builtins/exit.c \
				builtins/env.c \
				builtins/cd.c \
				builtins/cd_utils.c \
				builtins/unset.c \
				builtins/export.c \
				builtins/envp_utils.c \
				signals/signals.c \
				signals/sig_heredoc.c \
				builtins/utils.c \
				builtins/export_verify.c
SRCS = $(addprefix sources/, $(SRCS_FILES))
OBJS = $(SRCS:.c=.o)
INCLS = includes/

################################################################################
#                                      EXTRA                                   #
################################################################################

NLIBFTFILES := $(shell find ./sources/libft -name "*.c" | wc -l)
NFILES := $$(($(shell find ./sources -name "*.c" | wc -l) - $(NLIBFTFILES)))
COUNTER := 0

UPDATE = \033[0K\r
RESET = \033[0m
BOLD = \033[1m
WHITE = \033[1;37m
RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m

################################################################################
#                                    COMMANDS                                  #
################################################################################

all : $(NAME)

$(NAME) : $(OBJS)
	@make bonus -C $(LIBFT) --no-print-directory
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline $(LIBFT)/libft.a
	@echo "$(BOLD)[$(NAME)] : [$(BLUE)100$(WHITE)/$(BLUE)100$(WHITE)] [$(GREEN)✔️$(WHITE)]$(RESET)"
	@echo "$(BOLD)[$(NAME)] : [$(BLUE)binary$(WHITE)] [$(GREEN)✔️$(WHITE)]$(RESET)"

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(INCLS)
	@$(eval COUNTER := $(shell echo $$(($(COUNTER) + 1))))
	@printf "$(BOLD)[$(NAME)] : [$(BLUE)$(shell echo $$(($(COUNTER) * 100 / $(NFILES))))$(WHITE)/$(BLUE)100$(WHITE)]$(RESET)$(UPDATE)"

clean :
	@make clean -C $(LIBFT) --no-print-directory
	@rm -f $(OBJS)
	@echo "$(BOLD)[$(NAME)] : [$(BLUE)objects$(WHITE)] [$(RED)✘$(WHITE)]$(RESET)"

fclean : clean
	@make fclean -C $(LIBFT) --no-print-directory
	@rm -f $(NAME)
	@echo "$(BOLD)[$(NAME)] : [$(BLUE)binary$(WHITE)] [$(RED)✘$(WHITE)]$(RESET)"

re : fclean all

valgrind : all
	@clear
	@valgrind --quiet --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=valgrind.supp ./minishell

git : fclean
	@git add . > /dev/null 2>&1
	@git commit -m "$(m)" > /dev/null 2>&1
	@git push > /dev/null 2>&1
	@echo "$(BOLD)[$(NAME)] : [$(BLUE)github$(WHITE)] [$(GREEN)✔️$(WHITE)]$(RESET)"

.PHONY : all clean fclean re