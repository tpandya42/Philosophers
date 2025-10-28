NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -g

SRC_DIR = src
SRC = \
	$(SRC_DIR)/cleanup.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/monitoring.c \
	$(SRC_DIR)/monitoring_utils.c \
	$(SRC_DIR)/routine.c \
	$(SRC_DIR)/run_sim.c \
	$(SRC_DIR)/sync.c \
	$(SRC_DIR)/utilities.c \
	$(SRC_DIR)/util_01.c
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
