NAME	= philo

FILES	= src/checking.c \
			src/get_time.c \
			src/init_philo.c \
			src/init_rule.c \
			src/launch.c \
			src/main.c \
			src/printing.c \
			src/to_do.c \
			utils/ft_atoi.c \

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
