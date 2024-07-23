NAME	= philo

FILES	= src/philo.c \
			src/init.c \
			utils/ft_atoi.c \
			utils/error.c \
			utils/time.c \
			src/launch.c \

CC	= gcc

FLAG	= -Wall -Wextra -Werror

OFILES	= $(FILES:.c=.o)

$(NAME):
	$(CC) $(CFLAGS) $(FILES) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
