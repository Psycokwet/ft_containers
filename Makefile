# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/19 22:03:00 by scarboni          #+#    #+#              #
#    Updated: 2022/08/25 13:57:11 by scarboni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#
# -------------------------------- COLORS --------------------------------
#

RESET			= "\033[0m"
BLACK			= "\033[30m"
RED				= "\033[31m"
GREEN			= "\033[32m"
YELLOW			= "\033[33m"
BLUE			= "\033[34m"
MAGENTA			= "\033[35m"
CYAN			= "\033[36m"
WHITE			= "\033[37m"
BOLDBLACK		= "\033[1m\033[30m"
BOLDRED			= "\033[1m\033[31m"
BOLDGREEN		= "\033[1m\033[32m"
BOLDYELLOW		= "\033[1m\033[33m"
BOLDBLUE		= "\033[1m\033[34m"
BOLDMAGENTA		= "\033[1m\033[35m"
BOLDCYAN		= "\033[1m\033[36m"
BOLDWHITE		= "\033[1m\033[37m"

$(RESET)		= RESET
$(BLACK)		= BLACK
$(RED)			= RED
$(GREEN)		= GREEN
$(YELLOW)		= YELLOW
$(BLUE)			= BLUE
$(MAGENTA)		= MAGENTA
$(CYAN)			= CYAN
$(WHITE)		= WHITE
$(BOLDBLACK)	= BOLDBLACK
$(BOLDRED)		= BOLDRED
$(BOLDGREEN)	= BOLDGREEN
$(BOLDYELLOW)	= BOLDYELLOW
$(BOLDBLUE)		= BOLDBLUE
$(BOLDMAGENTA)	= BOLDMAGENTA
$(BOLDCYAN)		= BOLDCYAN
$(BOLDWHITE)	= BOLDWHITE

COLORS = 		$($(RESET))\
				$($(BLACK))\
				$($(RED))\
				$($(GREEN))\
				$($(YELLOW))\
				$($(BLUE))\
				$($(MAGENTA))\
				$($(CYAN))\
				$($(WHITE))\
				$($(BOLDBLACK))\
				$($(BOLDRED))\
				$($(BOLDGREEN))\
				$($(BOLDYELLOW))\
				$($(BOLDBLUE))\
				$($(BOLDMAGENTA))\
				$($(BOLDCYAN))\
				$($(BOLDWHITE))

DCOLORS :=  	$($(RESET))=$(RESET)\
				$($(BLACK))=$(BLACK)\
				$($(RED))=$(RED)\
				$($(GREEN))=$(GREEN)\
				$($(YELLOW))=$(YELLOW)\
				$($(BLUE))=$(BLUE)\
				$($(MAGENTA))=$(MAGENTA)\
				$($(CYAN))=$(CYAN)\
				$($(WHITE))=$(WHITE)\
				$($(BOLDBLACK))=$(BOLDBLACK)\
				$($(BOLDRED))=$(BOLDRED)\
				$($(BOLDGREEN))=$(BOLDGREEN)\
				$($(BOLDYELLOW))=$(BOLDYELLOW)\
				$($(BOLDBLUE))=$(BOLDBLUE)\
				$($(BOLDMAGENTA))=$(BOLDMAGENTA)\
				$($(BOLDCYAN))=$(BOLDCYAN)\
				$($(BOLDWHITE))=$(BOLDWHITE)

DCOLORS :=  	$(addprefix -D, $(DCOLORS))

#
# -------------------------------- Paths --------------------------------
#

INC_DIR					= srcs/containers/

LAST_RUN_LOGS_FOLDER	= logs
SAVED_LOGS_FOLDER		= pastLogs

TEST_SRCS				= test_srcs/
TEST_DATAS				= test_datas/
TEST_DATAS_GENERATED	= $(TEST_DATAS)generated/

OBJ_PATH				= bin/

SRC_PATH				= srcs/

CPP_EXTENSION 			= .cpp

UTIL_PATH				= util/
CONTAINERS_PATH			= containers/

OBJ_PATHS				+= $(OBJ_PATH) $(addprefix $(OBJ_PATH), $(UTIL_PATH) $(NETWORK_PATH) $(SERVER_PATH) )

ALL_PATHS_TO_INIT		= $(SAVED_LOGS_FOLDER) $(LAST_RUN_LOGS_FOLDER)

#
# -------------------------------- Rules names --------------------------------
#

CLEAN_UNWANTED_PATHS 	= CleanPreviousPaths
SAVE_LAST_LOGS 			= SaveLastLogs
NAME_STL				= containers_stl
NAME_MINE				= containers_moi
NAME					= containers
CLEAN_LOGS				= cleanLogs
COMPILE 				= compile


ALL_RULES_NAMES =		$(CLEAN_UNWANTED_PATHS) \
						$(SAVE_LAST_LOGS) \
						$(CLEAN_LOGS) \
						$(COMPILE)

ALL_EXECS_NAMES =		$(NAME_MINE) $(NAME_STL)

#
# -------------------------------- TEST SRCS definitions --------------------------------
#

GENERATE_EXAMPLES_REQUESTS_FILES = 	writeRequestsExamples

GENERATE_EXAMPLES_REQUESTS_SRCS_RAW += $(addprefix $(TEST_SRCS), $(GENERATE_EXAMPLES_REQUESTS_FILES))
GENERATE_EXAMPLES_REQUESTS_SRCS_RAW += $(UTIL_PATH)logger

GENERATE_EXAMPLES_REQUESTS_SRCS_EXT = $(addsuffix  $(CPP_EXTENSION), $(GENERATE_EXAMPLES_REQUESTS_SRCS_RAW))

GENERATE_EXAMPLES_REQUESTS_SRCS = $(addprefix  $(SRC_PATH), $(GENERATE_EXAMPLES_REQUESTS_SRCS_EXT))
#
# -------------------------------- SRCS definitions --------------------------------
#

CONTAINERS_FILES = 	#HERE
SRCS_FILES += $(addprefix $(CONTAINERS_PATH), $(CONTAINERS_FILES))

UTIL_FILES =	logger
SRCS_FILES += $(addprefix $(UTIL_PATH), $(UTIL_FILES))

#
# -------------------------------- Building configurations --------------------------------
#

CXX				= c++
CPPFLAGS		= -Wall -Wextra -Werror -std=c++98 -g  -MD  #-fsanitize=address
CPPFLAGS 		+= -DLOGS_FOLDER='"$(LAST_RUN_LOGS_FOLDER)"'

RM				= rm -f
# CPPFLAGS		+= $(DCOLORS)

LDFLAGS			= -I$(INC_DIR)

#
# -------------------------------- automated tests treatments --------------------------------
#

ifndef LEAKS
	# LEAKS = 
	LEAKS = valgrind --leak-check=full --show-leak-kinds=all
endif

ifndef TESTS
	TESTS=""
	SRCS_FILES += 	main
	CPPFLAGS += -DDEBUG=false
else
	CPPFLAGS += -DDEBUG=true
endif

SRCS_FILES_EXT 		+= 	$(addsuffix $(CPP_EXTENSION), $(SRCS_FILES))
SRCS 				+= 	$(addprefix $(SRC_PATH), $(SRCS_FILES_EXT))
OBJS 				= 	$(addprefix $(OBJ_PATH), $(SRCS_FILES_EXT:cpp=o))
OBJS_MINE			= 	$(addprefix $(OBJ_PATH), $(SRCS_FILES_EXT:cpp=o_mine.o))
DEPS 				= 	$(addprefix $(OBJ_PATH), $(SRCS_FILES_EXT:cpp=d))
-include $(DEPS)

#
# -------------------------------- FUNCTIONS --------------------------------
#

define colorize
	@echo -n $(1)
	@$(2)
	@echo -n $(RESET)
endef

#
# -------------------------------- Rules implementations --------------------------------
#

#
## -------------------------------- COMPILE --------------------------------
#

all: | $(CLEAN_UNWANTED_PATHS) $(ALL_PATHS_TO_INIT) $(NAME)

# $(OBJ_PATH)_mine/%.o: $(SRC_PATH)%.cpp 
# 	@mkdir -p $(dir $@)
$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp 
	@mkdir -p $(dir $@)
	${CXX} ${CPPFLAGS} $(LDFLAGS) -c $< -o $@
	${CXX} ${CPPFLAGS} $(LDFLAGS) -DSTL=true -c $< -o $@_mine.o

# $(COMPILE): $(OBJS)
# 	$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJS)

$(NAME_MINE):  $(OBJS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o $(NAME_MINE) $(OBJS_MINE)

$(NAME_STL):  $(OBJS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -DSTL=true -o $(NAME_STL) $(OBJS)

$(NAME): $(NAME_MINE) $(NAME_STL) 


SEED =42

test_main_42: re
	$(LEAKS) ./$(NAME_STL) $(SEED)
	@printf "\n____.--.--.____.--.--.____.--.--.____.--.--.__Weeeeeeeeee__.--.--.____.--.--.____.--.--.____.--.--.____\n\n"
	$(LEAKS) ./$(NAME_MINE) $(SEED)

#
## -------------------------------- LOGS --------------------------------
#

$(SAVE_LAST_LOGS)	:
	@echo "Saving previous logs"
	@mv  $(LAST_RUN_LOGS_FOLDER)  $(SAVED_LOGS_FOLDER)/$(shell date "+%y_%m_%d_%H_%M_%S")

$(CLEAN_UNWANTED_PATHS)	: 
	@echo "deleting previous run special paths..." $(LAST_RUN_LOGS_FOLDER)
	@rm -rf  $(LAST_RUN_LOGS_FOLDER) 

#
## -------------------------------- TESTS --------------------------------
#



#
## -------------------------------- OTHERS --------------------------------
#

$(ALL_PATHS_TO_INIT): 
	@echo "Generating bin folder and subfolders" $@
	@mkdir -p  $@  

$(CLEAN_LOGS):
	$(call colorize, $(YELLOW), \
		echo "Deleting last logs...";\
		rm -rf $(LAST_RUN_LOGS_FOLDER);\
	)
	
clean:  $(CLEAN_LOGS)
	$(call colorize, $(MAGENTA), \
		echo "Deleting objects...";\
		rm -rf $(OBJ_PATH);\
		echo "Deleted all but executable";\
	)

fclean:		clean
	$(call colorize, $(RED), \
		$(RM) $(ALL_EXECS_NAMES);\
		echo "Everything deleted";\
	)

re:			fclean all

.PHONY:		all clean fclean re $(ALL_RULES_NAMES)
