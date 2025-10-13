NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -g

SRC_DIR = src
SRC = \
	$(SRC_DIR)/cleanup.c \
	$(SRC_DIR)/initialization.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/monitoring.c \
	$(SRC_DIR)/monitoring_utils.c \
	$(SRC_DIR)/philosopher_actions.c \
	$(SRC_DIR)/simulation_runner.c \
	$(SRC_DIR)/synchronization.c \
	$(SRC_DIR)/utilities.c
OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INC_DIR = include
INC = -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "✅ Build complete!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "🔨 Compiling $<"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "🧹 Cleaned object files"

fclean: clean
	@rm -f $(NAME)
	@echo "🧹 Cleaned executable"

re: fclean all

.PHONY: all clean fclean re
