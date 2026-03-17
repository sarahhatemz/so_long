#include "so_long.h"
void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

int	check_path(char **map, t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (map[y][x] == 'C' || map[y][x] == 'E')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	validation(t_game *game)
{
	char	**cpy;
	int		result;

	cpy = copy_map(game);
	if (!cpy)
		return (0);
	flood_fill(cpy, game->px, game->py);
	result = check_path(cpy, game);
	free_pmap(cpy, game->height);
	return (result);
}


int	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(
			game->mlx,
			game->width * 64,
			game->height * 64,
			"so_long");
	if (!game->win)
		return (0);
	return (1);
}

void	*load_xpm(void *mlx, char *path)
{
	void	*img;
	int		w;
	int		h;

	img = mlx_xpm_file_to_image(mlx, path, &w, &h);
	if (!img)
		ft_printf("Error\nFailed to load image: %s\n", path);
	return (img);
}

int	load_images(t_game *game)
{
	game->img.wall = load_xpm(game->mlx, "images64/wall.xpm");
	game->img.floor = load_xpm(game->mlx, "images64/floor.xpm");
	game->img.player = load_xpm(game->mlx, "images64/player.xpm");
	game->img.collectable = load_xpm(game->mlx, "images64/collectable.xpm");
	game->img.exit = load_xpm(game->mlx, "images64/exit.xpm");
	if (!game->img.wall || !game->img.floor || !game->img.player
		|| !game->img.collectable || !game->img.exit)
		return (0);
	return (1);
}


void	put_image(t_game *g, int x, int y)
{
	mlx_put_image_to_window(g->mlx, g->win,
		g->img.floor, x * 64, y * 64);
	if (g->map[y][x] == '1')
		mlx_put_image_to_window(g->mlx, g->win,
			g->img.wall, x * 64, y * 64);
	else if (g->map[y][x] == 'P')
		mlx_put_image_to_window(g->mlx, g->win,
			g->img.player, x * 64, y * 64);
	else if (g->map[y][x] == 'C')
		mlx_put_image_to_window(g->mlx, g->win,
			g->img.collectable, x * 64, y * 64);
	else if (g->map[y][x] == 'E')
		mlx_put_image_to_window(g->mlx, g->win,
			g->img.exit, x * 64, y * 64);
}