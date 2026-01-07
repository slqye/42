################################################################################
#                                     CONFIG                                   #
################################################################################

NAME = braiiiiiiinnnzzzz
CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS_FILES	= main.cpp \
				Zombie.class.cpp \
				newZombie.cpp \
				randomChump.cpp
SRCS		= $(addprefix sources/, $(SRCS_FILES))
OBJS		= $(SRCS:.cpp=.o)
INCLS		= includes/

################################################################################
#                                      EXTRA                                   #
################################################################################

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
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) -I$(INCLS)
	@echo "$(BOLD)[$(NAME)] : [$(BLUE)binary$(WHITE)] [$(GREEN)✔️$(WHITE)]$(RESET)"

%.o : %.cpp
	@$(CXX) $(CXXFLAGS) -o $@ -c $< -I$(INCLS)

clean :
	@rm -f $(OBJS)
	@echo "$(BOLD)[$(NAME)] : [$(BLUE)objects$(WHITE)] [$(RED)✘$(WHITE)]$(RESET)"

fclean : clean
	@rm -f $(NAME)
	@echo "$(BOLD)[$(NAME)] : [$(BLUE)binary$(WHITE)] [$(RED)✘$(WHITE)]$(RESET)"

re : fclean all

.PHONY : all clean fclean re