#Program variables
NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

#Files variables
LIBFT = sources/libft
SRCS_FILES =	main.c \
				pipex.c \
				utils.c \
				pipex_limiter.c \
				get_next_line/get_next_line.c \
				get_next_line/get_next_line_utils.c
SRCS = $(addprefix sources/, $(SRCS_FILES))
OBJS = $(SRCS:.c=.o)
INCLS = includes/

#Extra variables
RESET = \033[1;39m
BOLD= \033[1m
GREEN= \033[1;32m
BLUE= \033[1;34m

#Commands
all : $(NAME)

$(NAME) : $(OBJS)
	@make -C $(LIBFT) --no-print-directory
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)/libft.a
	@echo "$(BOLD)|> $(BLUE)$(NAME) compiled.$(RESET)"

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(INCLS)

clean :
	@make clean -C $(LIBFT) --no-print-directory
	@rm -f $(OBJS)
	@echo "$(BOLD)|> $(GREEN)object files removed.$(RESET)"

fclean : clean
	@make fclean -C $(LIBFT) --no-print-directory
	@rm -f $(NAME)
	@echo "$(BOLD)|> $(GREEN)binary file removed.$(RESET)"

re : fclean all

.PHONY : all clean fclean re