NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -g

SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)
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

test: $(NAME)
	@echo "🧪 Running tests..."
	@echo "Test 1: Single philosopher (should die)"
	@timeout 5s ./$(NAME) 1 800 200 200 || true
	@echo "\nTest 2: 4 philosophers, no death"
	@timeout 10s ./$(NAME) 4 800 200 200 || true
	@echo "\nTest 3: 5 philosophers with meal limit"
	@timeout 10s ./$(NAME) 5 800 200 200 5 || true

.PHONY: all clean fclean re test