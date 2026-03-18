CC      = cc
CFLAGS  = -Wall -Werror -Wextra
MFLAGS  = -Lminilibx-linux -lmlx -lXext -lX11 -lm

SRCS    = main.c check.c flood.c last.c map_op.c map_read.c new.c
OBJ     = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_A   = libft/libft.a
MLX_DIR   = minilibx-linux
MLX_A     = minilibx-linux/libmlx.a

NAME = so_long

all: $(MLX_A) $(NAME)

$(MLX_A):
		echo "Cloning MiniLibX..."; \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ) $(LIBFT_A) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJ) $(MFLAGS) -o $@ -L$(LIBFT_DIR) -lft

$(LIBFT_A):
	make -C $(LIBFT_DIR)



clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -rf $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re