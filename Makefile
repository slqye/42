################################################################################
#                                     CONFIG                                   #
################################################################################

NAME = philosophers
CC = cc
CFLAGS = -Wall -Werror -Wextra

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS_FILES =	main.c \
				lib/ft_atol.c \
				lib/ft_error.c \
				lib/ft_strlen.c \
				philosophers/philosophers.c \
				philosophers/philosophers_utils.c \
				threads/threads.c \
				threads/routines.c \
				threads/routines_utils.c \
				threads/master.c
SRCS = $(addprefix sources/, $(SRCS_FILES))
OBJS = $(SRCS:.c=.o)
INCLS = includes/

################################################################################
#                                      EXTRA                                   #
################################################################################

NFILES := $(shell find ./sources -name "*.c" | wc -l)
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
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(BOLD)[$(NAME)] : [$(BLUE)100$(WHITE)/$(BLUE)100$(WHITE)] [$(GREEN)✔️$(WHITE)]$(RESET)"
	@echo "$(BOLD)[$(NAME)] : [$(BLUE)binary$(WHITE)] [$(GREEN)✔️$(WHITE)]$(RESET)"

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(INCLS)
	@$(eval COUNTER := $(shell echo $$(($(COUNTER) + 1))))
	@printf "$(BOLD)[$(NAME)] : [$(BLUE)$(shell echo $$(($(COUNTER) * 100 / $(NFILES))))$(WHITE)/$(BLUE)100$(WHITE)]$(RESET)$(UPDATE)"

clean :
	@rm -f $(OBJS)
	@echo "$(BOLD)[$(NAME)] : [$(BLUE)objects$(WHITE)] [$(RED)✘$(WHITE)]$(RESET)"

fclean : clean
	@rm -f $(NAME)
	@echo "$(BOLD)[$(NAME)] : [$(BLUE)binary$(WHITE)] [$(RED)✘$(WHITE)]$(RESET)"

re : fclean all

.PHONY : all clean fclean re