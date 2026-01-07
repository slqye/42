# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlederge <nlederge@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/19 15:24:15 by nlederge          #+#    #+#              #
#    Updated: 2024/10/28 16:19:31 by nlederge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### Global

NAME		= webserv
	
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -g
RM			= rm -rf

### Sources and objects

MAIN_SOURCES	= main.cpp \

CLASS_SOURCES	= Webserv.cpp \
					Network.cpp \
					Server.cpp \
					Location.cpp \
					CGI.cpp \
					Response.cpp \
					Log.cpp \
					ConfigParser.cpp \
					CGIExecutor.cpp \

UTILS_SOURCES	= numbers_utils.cpp \
					string_utils.cpp

MAIN_SOURCES_PREFIX	= $(addprefix sources/, $(MAIN_SOURCES))
CLASS_SOURCES_PREFIX	= $(addprefix sources/class/, $(CLASS_SOURCES))
UTILS_SOURCES_PREFIX	= $(addprefix sources/utils/, $(UTILS_SOURCES))

MAIN_OBJECTS	= $(MAIN_SOURCES_PREFIX:.cpp=.o)
CLASS_OBJECTS	= $(CLASS_SOURCES_PREFIX:.cpp=.o)
UTILS_OBJECTS	= $(UTILS_SOURCES_PREFIX:.cpp=.o)

OBJECTS		= $(MAIN_OBJECTS) $(CLASS_OBJECTS) $(UTILS_OBJECTS)

### Includes

INCLUDES = -I./includes

### Colors

DFLT_COLOR	= \033[0;39m
GREEN		= \033[0;92m
RED			= \033[0;91m

### Rules

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ 

$(NAME): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJECTS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(DFLT_COLOR)"

all: $(NAME)

clean:
	@$(RM) $(OBJECTS)
	@echo "$(RED)objects removed!$(DFLT_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)$(NAME) removed!$(DFLT_COLOR)"

re: fclean all

clear:
	@clear && clear

execute:
	@valgrind ./webserv

valgrind: clear all execute

revalgrind: clear re execute

.PHONY: all clean fclean re clear execute valgrind