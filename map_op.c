/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salzghou <salzghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:24:00 by salzghou          #+#    #+#             */
/*   Updated: 2026/03/18 20:11:45 by salzghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	while (i < game->height && store_line(game, fd, i))
		i++;
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

int	storing_map(t_game *game, char *mapname)
{
	int	fd;

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
}

void	init_img(t_image *img)
{
	img->wall = NULL;
	img->floor = NULL;
	img->player = NULL;
	img->collectable = NULL;
	img->exit = NULL;
}

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->width = 0;
	game->height = 0;
	game->e_count = 0;
	game->c_count = 0;
	game->ex = 0;
	game->ey = 0;
	game->p_count = 0;
	game->px = 0;
	game->py = 0;
	game->moves = 0;
	game->on_exit = 0;
	init_img(&game->img);
}
