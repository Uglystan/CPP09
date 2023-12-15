NAME = btc
CC = c++
FLAGS = -Wall -Wextra -Werror
C98 = -std=c++98
RM = rm -rf

OBJ_DIR = objdep

SRC =	main.cpp \
	BitcoinExchange.cpp \

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.cpp=.o))
DEP = $(OBJ:.o=.d)

$(OBJ_DIR)/%.o : %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) $(C98) -MMD -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(C98) $(OBJ) -o $(NAME)

all : $(NAME)

clean : 
	@$(RM) $(OBJ) $(DEP)

fclean : clean
	@$(RM) $(NAME) $(OBJ_DIR)

re : fclean all

-include $(DEP)