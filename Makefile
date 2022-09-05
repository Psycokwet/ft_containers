

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/28 22:36:55 by saray             #+#    #+#              #
#    Updated: 2022/03/15 15:58:38 by scarboni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				= executable
NAME_TEST_MISC_STL 	= _TEST_MISC_STL
NAME_TEST_MISC_MINE	= _TEST_MISC_MINE
NAME_TEST_42_STL 	= _TEST_42_STL
NAME_TEST_42_MINE	= _TEST_42_MINE
NAME_TEST_TIME_STL 	= _TEST_TIME_STL
NAME_TEST_TIME_MINE	= _TEST_TIME_MINE

OBJ_PATH			= bin/

CXX 				= c++

CPPFLAGS 			= -Wall -Wextra -Werror -g3 -std=c++98

SRC_PATH			= ./srcs/

SRCS = 	main.cpp 	main_42.cpp 	main_time.cpp 

LDFLAGS			= -Isrcs/containers/

SRC_FILES	+=	$(SRCS)

OBJ_TEST_MISC 		= 	$(addprefix $(OBJ_PATH), $(SRC_FILES:cpp=o))

OBJ_PATHS_INIT			= $(OBJ_PATH)

all: $(NAME)

$(OBJ_PATHS_INIT)	:
	@echo "Generating bin folder and subfolders" $@
	@mkdir -p  $@  

$(NAME_TEST_MISC_STL): $(OBJ_PATHS_INIT)  $(OBJ_TEST_MISC)
	$(CXX) $(CPPFLAGS) -o $(NAME_TEST_MISC_STL) $(OBJ_PATH)main.o $(LDFLAGS) -DSTL=true
$(NAME_TEST_MISC_MINE): $(OBJ_PATHS_INIT)  $(OBJ_TEST_MISC)
	$(CXX) $(CPPFLAGS) -o $(NAME_TEST_MISC_MINE) $(OBJ_PATH)main.omine.o $(LDFLAGS)

$(NAME_TEST_42_STL): $(OBJ_PATHS_INIT)  $(OBJ_TEST_MISC)
	$(CXX) $(CPPFLAGS) -o $(NAME_TEST_42_STL) $(OBJ_PATH)main_42.o $(LDFLAGS) -DSTL=true
$(NAME_TEST_42_MINE): $(OBJ_PATHS_INIT)  $(OBJ_TEST_MISC)
	$(CXX) $(CPPFLAGS) -o $(NAME_TEST_42_MINE) $(OBJ_PATH)main_42.omine.o $(LDFLAGS)

$(NAME_TEST_TIME_STL): $(OBJ_PATHS_INIT)  $(OBJ_TEST_MISC)
	$(CXX) $(CPPFLAGS) -o $(NAME_TEST_TIME_STL) $(OBJ_PATH)main_time.o $(LDFLAGS) -DSTL=true
$(NAME_TEST_TIME_MINE): $(OBJ_PATHS_INIT)  $(OBJ_TEST_MISC)
	$(CXX) $(CPPFLAGS) -o $(NAME_TEST_TIME_MINE) $(OBJ_PATH)main_time.omine.o $(LDFLAGS)

$(NAME): $(NAME_TEST_MISC_STL)  $(NAME_TEST_MISC_MINE)

test_misc: $(NAME_TEST_MISC_STL)  $(NAME_TEST_MISC_MINE)
	valgrind ./$(NAME_TEST_MISC_STL) > logs/$(NAME_TEST_MISC_STL) 
	valgrind ./$(NAME_TEST_MISC_MINE) > logs/$(NAME_TEST_MISC_MINE) 
	diff logs/$(NAME_TEST_MISC_STL) logs/$(NAME_TEST_MISC_MINE) 

test_42: $(NAME_TEST_42_STL)  $(NAME_TEST_42_MINE)
	valgrind ./$(NAME_TEST_42_STL) 42 > logs/$(NAME_TEST_42_STL) 
	valgrind ./$(NAME_TEST_42_MINE) 42 > logs/$(NAME_TEST_42_MINE) 
	diff logs/$(NAME_TEST_42_STL) logs/$(NAME_TEST_42_MINE) 

test_time: $(NAME_TEST_TIME_STL)  $(NAME_TEST_TIME_MINE)
	 ./$(NAME_TEST_TIME_STL) 42 > logs/$(NAME_TEST_TIME_STL) 
	 ./$(NAME_TEST_TIME_MINE) 42 > logs/$(NAME_TEST_TIME_MINE) 
	diff logs/$(NAME_TEST_TIME_STL) logs/$(NAME_TEST_TIME_MINE) 

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp $(HEADERS_FILES)
	${CXX} ${CPPFLAGS}   -c $< -o $@  $(LDFLAGS) 
	${CXX} ${CPPFLAGS}   -c $< -o $@mine.o -DSTL=true $(LDFLAGS) 

clean:
	@echo "\033[0;31m\nDeleting objects..."
	@rm -rf $(OBJ_PATH)
	@echo "\033[0m"

fclean:
	@echo "\033[0;31m\nDeleting objects..."
	@rm -rf $(OBJ_PATH)
	@echo "\nDeleting executable..."
	@rm -f $(NAME) $(NAME_TEST_MISC_STL)  $(NAME_TEST_MISC_MINE)
	@echo "\033[0m"		

re: fclean all

# LEAKS = valgrind 
LEAKS = 

test:	$(NAME)
	$(LEAKS) ./$(NAME)

.PHONY: clean fclean re bonus