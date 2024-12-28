CC = cc
NAME = philo
CFLAGS = -Wall -Wextra -Werror
SRC =	g_c.c init_data.c main.c routine.c utils.c
OBJ = ${SRC:.c=.o}

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
