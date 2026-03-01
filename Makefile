CC = cc

CFLAGS = -Wall -Werror -Wextra 

MFLAGS = -Lminilibx-linux -lmlx -lXext -lX11

SRCS =   main.c

OBJ = $(SRCS:.c=.o)

LIBFT_DIR = libft

LIBFT_A = libft/libft.a

NAME = so_long

all: $(NAME)

$(NAME) : $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ) $(MFLAGS) -o $@ -L $(LIBFT_DIR) -lft

$(LIBFT_A) :
	make -C $(LIBFT_DIR)
clean :
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJ)
fclean : clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re