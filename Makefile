NAME = push_swap

SRC = arg_check.c	commands.c	end_prog.c	getters.c	helpers.c \
		main.c	order_big.c	order_small.c	parse.c

OBJ = $(SRC:.c=.o)
DEPENDENCY = -Llibft -lft

LIBFT = libft/libft.a

CC = cc
FLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(DEPENDENCY) -o $(NAME)
	@echo "\e[0;32mPush Swap compiled!\e[0m"

$(LIBFT):
	@echo "LIBFT:\e[0;33m Ensuring submodule is initialized...\e[0m"
	@git submodule update --init --recursive --force libft
	@echo "LIBFT:\e[0;32m Libft ready.\e[0m"
	@$(MAKE) bonus -C libft/ --no-print-directory;

# Regra padrão para compilar .c -> .o
%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "Compiled $< -> $@"

clean:
	@/bin/rm -f *.o
	@$(MAKE) clean -C libft/ --no-print-directory
	@echo "\e[0;33mPush Swap clean done!\e[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@$(MAKE) fclean -C libft/ --no-print-directory
	@echo "\e[0;31mPush Swap fclean done!\e[0m"

re: fclean all

.PHONY: all clean fclean re