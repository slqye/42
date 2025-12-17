NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS_FILES = 	ft_printf.c \
				ft_utils.c \
				ft_convert/ft_convert_c.c \
				ft_convert/ft_convert_d.c \
				ft_convert/ft_convert_i.c \
				ft_convert/ft_convert_p.c \
				ft_convert/ft_convert_s.c \
				ft_convert/ft_convert_u.c \
				ft_convert/ft_convert_x.c \
				ft_convert/ft_convert_xx.c
SRCS = $(addprefix sources/, $(SRCS_FILES))
OBJ = $(SRCS:.c=.o)

#Extra variables
RESET = \033[1;39m
BOLD= \033[1m
GREEN= \033[1;32m
BLUE= \033[1;34m

all : $(NAME)

$(NAME) : $(OBJ)
	@ar cr $(NAME) $(OBJ)
	@echo "$(BOLD)[$(NAME)] Makefile : $(GREEN)Library created successfully!$(RESET)"

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $<
	@echo "$(BOLD)[$(NAME)] Makefile : $(BLUE)Scripts compiled.$(RESET)"

clean :
	@rm -f $(OBJ) $(OBJB)
	@echo "$(BOLD)[$(NAME)] Makefile : $(BLUE)Objects files removed.$(RESET)"

fclean : clean
	@rm -f $(NAME)
	@echo "$(BOLD)[$(NAME)] Makefile : $(BLUE)Executable removed.$(RESET)"

re : fclean all

.PHONY : all clean fclean re