NAME = ./pipex
NAME_BONUS = ./pipex_bonus
LIBFT_PATH = ./Libft
LIBFT = $(LIBFT_PATH)/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
PATH_SRC = srcs
FILES = pipex.c exec_utils.c parse_utils.c
SRC = $(addprefix $(PATH_SRC)/,$(FILES))
PATH_SRC_BONUS = srcs_bonus
FILES_BONUS = pipex_bonus.c
SRC_BONUS = $(addprefix $(PATH_SRC_BONUS)/,$(FILES_BONUS))
RM = rm -rf
VAL = valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind.txt

all: $(NAME)

bonus: $(NAME_BONUS)

$(LIBFT):
	@make -C $(LIBFT_PATH) --no-print-directory

$(NAME): $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LIBFT)

$(NAME_BONUS): $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(SRC_BONUS) $(LIBFT)
	@cp ./pipex_bonus ./pipex

clean:
	make clean -C $(LIBFT_PATH)

fclean: clean
	make fclean -C $(LIBFT_PATH) 
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re

