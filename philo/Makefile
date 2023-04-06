NAME = philo

CC = gcc
CFLAGS = -pthread -Wall -Werror -Wextra -g
CFILES = main.c parce_input.c actions.c utils.c init.c pthread.c
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

norm:
	norminette *
