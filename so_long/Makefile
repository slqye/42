#Program variables
NAME = so_long
CC = cc
CFLAGS = -Wall -Werror -Wextra
#Files variables
LIBFT = sources/libft
SRCS_FILES =	sources/main.c \
				sources/get_next_line/get_next_line.c \
				sources/get_next_line/get_next_line_utils.c \
				sources/map/map.c \
				sources/map/map_checks.c \
				sources/map/map_checks_utils.c \
				sources/map/map_pathfinder.c \
				sources/map/map_pathfinder_utils.c \
				sources/rw_mlx/rw_mlx.c \
				sources/rw_mlx/rw_mlx_utils.c \
				sources/rw_mlx/rw_mlx_window.c \
				sources/player/player.c \
				sources/common.c
SRCS = $(SRCS_FILES)
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
	@$(CC) $(CFLAGS) $(OBJS) -L. -lmlx -L/usr/lib -Iminilibx -lXext -lX11 -lm -lz -o $(NAME) $(LIBFT)/libft.a
	@echo "$(BOLD)[$(NAME)] Makefile : $(GREEN)Executable created successfully!$(RESET)"
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLS) -I/usr/include -Imlx -O3
	@echo "$(BOLD)[$(NAME)] Makefile : $(BLUE)Scripts compiled.$(RESET)"

clean :
	@make clean -C $(LIBFT) --no-print-directory
	@rm -f $(OBJS)
	@echo "$(BOLD)[$(NAME)] Makefile : $(BLUE)Objects files removed.$(RESET)"

fclean : clean
	@make fclean -C $(LIBFT) --no-print-directory
	@rm -f $(NAME)
	@echo "$(BOLD)[$(NAME)] Makefile : $(BLUE)Executable removed.$(RESET)"

re : fclean all

.PHONY : all clean fclean re