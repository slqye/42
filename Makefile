################################################################################
#                                     CONFIG                                   #
################################################################################

NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

LIBFT = sources/libft
SRCS_FILES =	main.c \
					utils.c \
					memory.c \
					parser/parser.c \
					parser/parser_utils.c \
					parser/parser_grid.c \
					parser/checker.c \
					parser/checker_utils.c \
					render/window.c \
					render/hooks.c \
					render/player.c \
					render/raycasting.c \
					render/raycasting_utils.c \
					render/ray_horizontal.c \
					render/ray_vertical.c \
					render/picture.c \
					render/minimap.c \
					get_next_line/get_next_line.c \
					get_next_line/get_next_line_utils.c
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
	cd MLX42 && cmake -B build
	cd MLX42 && cmake --build build -j4
	@make bonus -C $(LIBFT) --no-print-directory
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)/libft.a MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm
	@echo "$(BOLD)[$(NAME)] : [$(BLUE)binary$(WHITE)] [$(GREEN)✔️$(WHITE)]$(RESET)"

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(INCLS)

clean :
	@make clean -C $(LIBFT) --no-print-directory
	@rm -f $(OBJS)
	@echo "$(BOLD)[$(NAME)] : [$(BLUE)objects$(WHITE)] [$(RED)✘$(WHITE)]$(RESET)"

fclean : clean
	@rm -rf MLX42/build
	@make fclean -C $(LIBFT) --no-print-directory
	@rm -f $(NAME)
	@echo "$(BOLD)[$(NAME)] : [$(BLUE)binary$(WHITE)] [$(RED)✘$(WHITE)]$(RESET)"

re : fclean all

.PHONY : all clean fclean re