#include "so_long.h"

int open_map(char *mapname)
{
    int fd;
    int len;

    len = ft_strlen(mapname);
    if (len < 5
        || mapname[len - 4] != '.'
        || mapname[len - 3] != 'b'
        || mapname[len - 2] != 'e'
        || mapname[len - 1] != 'r')
    {
        ft_printf("Error\nInvalid map extension\n");
        return (-1); //exit
    }

    fd = open(mapname, O_RDONLY);
    if (fd < 0)
    {
        ft_printf("Error\nFailed to open map\n");
        return (-1); //exit
    }
    return (fd);
}

int	map_height(int fd)
{
	char	*line;
	int		count;

	count = 0;
	while ((line = get_next_line(fd)))
	{
		check_newline(line);
		if (line[0] == '\0')
		{
			free(line);
			return (-1);
		}
		count++;
		free(line);
	}
	if (count == 0)
		return (-1);
	return (count);
}
void	check_newline(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	while (i > 0 && (line[i - 1] == '\n' || line[i - 1] == '\r'))
	{
		line[i - 1] = '\0';
		i--;
	}
}
void	free_pmap(char **map, int fill)
{
	while (fill > 0)
		free(map[--fill]);
	free(map);
}

int	alloc_map(t_game *game)
{
	game->map = malloc(sizeof(char *) * (game->height + 1));
	if (!game->map)
		return (0);
	return (1);
}

int	store_line(t_game *game, int fd, int i)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (0);

	check_newline(line);
	if (line[0] == '\0')
	{
		free(line);
		return (0);
	}
	game->map[i] = ft_strdup(line);
	free(line);
	if (!game->map[i])
		return (0);
	return (1);
}
int	fill_map(t_game *game, char *mapname)
{
	int	fd;
	int	i;

	fd = open_map(mapname);
	if (fd < 0)
		return (0);
	i = 0;
	while (i < game->height)
{
    if (!store_line(game, fd, i))
        break;
    i++;
}
if (i != game->height)
{
    close(fd);
    free_pmap(game->map, i);
    game->map = NULL;
    return (0);
}
	game->map[i] = NULL;
	close(fd);
	return (1);
}

/*int storing_map(t_game *game, char *mapname)
{
    int fd;

    fd = open_map(mapname);
    if (fd < 0)
        return (0);
    game->height = map_height(fd);
    close(fd);
    if (game->height < 0)
        return (0);
    if (!alloc_map(game))
        return (0);
    if (!fill_map(game, mapname))
        return (0);
    return (1);
}*/
int storing_map(t_game *game, char *mapname)
{
    int fd;

    fd = open_map(mapname);
    if (fd < 0)
    {
        printf("OPEN FAILED\n");
        return (0);
    }

    game->height = map_height(fd);
    printf("HEIGHT = %d\n", game->height);

    close(fd);
    if (game->height < 0)
    {
        printf("HEIGHT FAILED\n");
        return (0);
    }

    if (!alloc_map(game))
    {
        printf("ALLOC FAILED\n");
        return (0);
    }

    if (!fill_map(game, mapname))
    {
        printf("FILL FAILED\n");
        return (0);
    }

    return (1);
}
void init_game(t_game *game)
{
    game->mlx = NULL;
    game->win = NULL;
    game->map = NULL;
    game->width = 0;
    game->height = 0;
    game->e_count = 0;
    game->c_count = 0;
    game->p_count = 0;
    game->px = 0;
    game->py = 0;
    game->moves = 0;

    init_img(&game->img);
}
void init_img(t_image *img)
{
    img->wall = NULL;
    img->floor = NULL;
    img->player = NULL;
    img->collectable = NULL;
    img->exit = NULL;
}
int check_rec(t_game *game)
{
    size_t fline;
    int i;

    fline = ft_strlen(game->map[0]);
    game->width = fline;
    i = 0;
    while (i < game->height)
    {
        if (ft_strlen(game->map[i]) != fline)
        {
            ft_printf("Error\nMap is not rectangular\n");
            return (0);
        }
        i++;
    }
    return (1);
}
int checkwalls(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (i < game->width)
    {
        if (game->map[0][i] != '1'
            || game->map[game->height - 1][i] != '1')
            return (0);
        i++;
    }
    j = 0;
    while (j < game->height)
    {
        if (game->map[j][0] != '1'
            || game->map[j][game->width - 1] != '1')
            return (0);
        j++;
    }
    return (1);
}
int	check_chars(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			c = game->map[y][x];
			if (c == 'P')
				(game->p_count++, game->px = x, game->py = y);
			else if (c == 'E')
				game->e_count++;
			else if (c == 'C')
				game->c_count++;
			else if (c != '0' && c != '1')
				return (0);
			x++;
		}
		y++;
	}
	return (game->p_count == 1 && game->e_count > 0 && game->c_count > 0);
}

char **restore(t_game *game)
{
    char **fmap;
    int i;

    i=0;
    fmap=malloc(sizeof(char *)*(game->height+1));
    if (!fmap)
        return (NULL);
    while(i<game->height)
    {
        fmap[i]=ft_strdup(game->map[i]);
        if(!fmap[i])
            return(NULL);
        i++;
    }
fmap[i]=NULL;
return(fmap);
}

void flood_fill(char **map ,int x, int y)
{

    if(map[y][x]=='1' || map[y][x]=='V')
        return ;
    map[y][x]='V';
    flood_fill(map,x+1,y);
    flood_fill(map,x-1,y);
    flood_fill(map,x,y+1);
    flood_fill(map,x,y-1);

}
int check_path(char **map,t_game *game)
{
    int y;
    int x;

    y=0;
    while(y<game->height)
    {
        x=0;
        while(x< game->width)
        {
            if(map[y][x] == 'C' || map[y][x]== 'E')
            return(0);
            x++;
        }
        y++;
    }
return(1);
}

int validation(t_game *game)
{
char **cpy;
cpy=restore(game);
if(!cpy)
    return(0);
flood_fill(cpy,game->px,game->py);
if(!check_path(cpy,game))
{
    free_pmap(cpy,game->height);
    return(0);
}
free_pmap(cpy,game->height);
return(1);
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
		ft_printf("IMG FAIL: %s\n", path);
	else
		ft_printf("IMG OK:   %s (%dx%d)\n", path, w, h);
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
}void put_image(t_game *g, int x, int y)
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

void draw_map(t_game *g)
{
    int y;
    int x;

    y = 0;
    while (y < g->height)
    {
        x = 0;
        while (x < g->width)
        {
            put_image(g, x, y);
            x++;
        }
        y++;
    }
}
static void	try_move(t_game *g, int dx, int dy)
{
	int		nx;
	int		ny;
	char	t;

	nx = g->px + dx;
	ny = g->py + dy;
	t = g->map[ny][nx];

	if (t == '1')
		return ;
	if (t == 'E' && g->c_count != 0)
		return ;

	if (t == 'C')
	{
		g->c_count--;
		g->map[ny][nx] = '0';
	}
	if (t == 'E' && g->c_count == 0)
	{
		ft_printf("You won in %d moves!\n", g->moves + 1);
		close_hook(g);
	}

	g->map[g->py][g->px] = '0';
	g->px = nx;
	g->py = ny;
	g->map[g->py][g->px] = 'P';

	g->moves++;
	ft_printf("Moves: %d\n", g->moves);
	draw_map(g);
}

int	key_hook(int keycode, t_game *g)
{
	if (keycode == 65307) /* ESC (Linux) */
		close_hook(g);
	else if (keycode == 'w' || keycode == 119 || keycode == 65362) /* W or Up */
		try_move(g, 0, -1);
	else if (keycode == 's' || keycode == 115 || keycode == 65364) /* S or Down */
		try_move(g, 0, 1);
	else if (keycode == 'a' || keycode == 97 || keycode == 65361)  /* A or Left */
		try_move(g, -1, 0);
	else if (keycode == 'd' || keycode == 100 || keycode == 65363) /* D or Right */
		try_move(g, 1, 0);
	return (0);
}

int	close_hook(t_game *g)
{
	if (g->img.wall) mlx_destroy_image(g->mlx, g->img.wall);
	if (g->img.floor) mlx_destroy_image(g->mlx, g->img.floor);
	if (g->img.player) mlx_destroy_image(g->mlx, g->img.player);
	if (g->img.collectable) mlx_destroy_image(g->mlx, g->img.collectable);
	if (g->img.exit) mlx_destroy_image(g->mlx, g->img.exit);

	if (g->win) mlx_destroy_window(g->mlx, g->win);
	/* Linux MLX usually needs these two: */
	mlx_destroy_display(g->mlx);
	free(g->mlx);

	if (g->map) free_pmap(g->map, g->height);
	exit(0);
	return (0);
}

int main(int argc, char *argv[])
{
    t_game game;

    if (argc != 2)
    {
        ft_printf("Error\nInvalid number of arguments\n");
        return (1);
    }

    init_game(&game);

    if (!storing_map(&game, argv[1])){
       
    return (1);
    }
    

    if (!check_rec(&game))
    {
        free_pmap(game.map, game.height);
        return (1);
    }

    if (!checkwalls(&game))
    {
        ft_printf("Error\nMap is not closed by walls\n");
        free_pmap(game.map, game.height);
        return (1);
    }

    if (!check_chars(&game))
    {
        ft_printf("Error\nInvalid map elements\n");
        free_pmap(game.map, game.height);
        return (1);
    }

    if (!validation(&game))
    {
        ft_printf("Error\nInvalid path\n");
        free_pmap(game.map, game.height);
        return (1);
    }

    if (!init_window(&game))
    {
        free_pmap(game.map, game.height);
        return (1);
    }

    if (!load_images(&game))
    {
        free_pmap(game.map, game.height);
        return (1);
    }
    draw_map(&game);
    mlx_loop(game.mlx);
    return (0);
}
