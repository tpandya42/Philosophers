NAME = philo
CC = cc
CFLAGS = -wall -werror -wextra -pthread

SRC_DIR = src 
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INC_DIR = include
INC = -I$(INC_DIR)

all: $(NAME)
	@$(MAKE) -C $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
fclean: clean
	@rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re

