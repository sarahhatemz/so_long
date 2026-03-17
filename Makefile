CC      = cc
CFLAGS  = -Wall -Werror -Wextra
MFLAGS  = -Lminilibx-linux -lmlx -lXext -lX11 -lm

SRCS    = main.c check.c flood.c last.c map_op.c map_read.c
OBJ     = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_A   = libft/libft.a
MLX_DIR   = minilibx-linux
MLX_A     = minilibx-linux/libmlx.a

NAME = so_long

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJ) $(MFLAGS) -o $@ -L$(LIBFT_DIR) -lft

$(LIBFT_A):
	make -C $(LIBFT_DIR)

$(MLX_A):
	@if [ ! -d "$(MLX_DIR)" ] || [ ! -f "$(MLX_DIR)/mlx.h" ]; then \
		echo "Cloning MiniLibX..."; \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	make -C $(MLX_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -rf $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re