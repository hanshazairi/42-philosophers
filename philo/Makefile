NAME = philo
SOURCES = philo.c utils.c libft_utils.c
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) $?

clean:
	$(RM) $(OBJECTS)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
