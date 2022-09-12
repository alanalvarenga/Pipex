NAME = pipex.a
#NAME_BONUS = pipex_bonus.a
LIBFT_PATH = ./Libft
INCLUDE = pipex.h
#INCLUDE_BONUS = pipex_bonus.h
LIBFT = $(LIBFT_PATH)/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
PATH_SRC = ./SRC/
PATH_SRC_BONUS = ./SRC_BONUS/
FILES = pipex.c exec_utils.c
OBJECTS = $(FILES:.c=.o)
#FILES_BONUS =
#OBJECTS_BONUS = $(FILES_BONUS:.c=.o)
RM = rm -f

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJECTS)
		@ make -C $(LIBFT_PATH)
		@ mv $(LIBFT) $(NAME)
		@ ar -rcs $(NAME) $(OBJECTS) $(INCLUDE)

$(PATH_SRC)%.o: $(PATH_SRC)%.c $(INCLUDE)
		@ $(CC) $(CFLAGS) -c $< -o $@

#$(NAME_BONUS): $(OBJECTS_BONUS) 
#		@ make -C $(LIBFT_PATH)
#		@ cp $(LIBFT) $(NAME_BONUS)
#		@ mv $(LIBFT) $(NAME_BONUS)
#		@ ar -rcs $(NAME_BONUS) $(OBJECTS_BONUS) $(INCLUDE_BONUS)
#		@ cp $(NAME_BONUS) $(NAME)

#$(PATH_SRC_BONUS)%.o: $(PATH_SRC_BONUS)%.c $(INCLUDE_BONUS)
#		@ $(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_PATH)
	$(RM) $(OBJECTS) $(OBJECTS_BONUS)

fclean: clean
	make fclean -C $(LIBFT_PATH) 
	$(RM) $(NAME)
#$(NAME_BONUS)

re: fclean all

testm: 
	$(CC) $(CFLAGS) -o pipex $(FILES) $(NAME)

testb:
	gcc main2.c -g $(CFLAGS) && ./a.out
# $(NAME_BONUS)
.PHONY: all clean fclean re

