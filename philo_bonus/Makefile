NAME = philo

CC = cc
CFLAGS = -pthread -Wall -Werror -Wextra -g
CFILES = main.c utils.c parse_input.c init.c eat_sleep_think.c free.c
OBJECTS = $(CFILES:%.c=$(OBJ_DIR)/%.o)
HEADER = src/philo.h
SRC_DIR = src
OBJ_DIR = obj

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean
