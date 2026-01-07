CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -Wno-deprecated-copy -std=c++11
NAME = bin.out
SRCS_CPP = $(wildcard ./sources/*.cpp)
OBJS = $(SRCS_CPP:.cpp=.o)
INCLS = includes/

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME) -I$(INCLS)
	@echo "Binary successfully compiled."

%.o : %.cpp
	@$(CXX) $(CXXFLAGS) -o $@ -c $< -I$(INCLS)

clean :
	@rm -f $(OBJS)
	@echo "Objects successfully removed."

fclean : clean
	@rm -f $(NAME)
	@echo "Binary successfully removed."

re : fclean all

test: all clean
	@./${NAME} ${ex}

.PHONY : all clean fclean re test
