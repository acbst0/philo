NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = src/philosphers.c \
		src/thread_routine.c \
		src/time.c \
		src/utils.c \
		src/ft_atoi.c \
		src/main.c \

OBJ = $(SRC:.c=.o)

.c.o:
	@$(CC) $(CFLAGS) $< -o $@

$(NAME):
		$(CC) $(SRC) $(CFLAGS) -o $(NAME)

all: $(NAME)

clean:
		@rm -rf $(OBJ)

fclean: clean
		@rm -rf $(NAME)

re:	fclean all

.PHONY: all clean fclean re
