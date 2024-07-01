NAME = philo
SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, main.c utils.c prog.c init.c checks.c)
CFLAGS = -Wall -Wextra -Werror -pthread
CC = cc

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) $(SRC) -o $(NAME) $(CFLAGS)


clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
