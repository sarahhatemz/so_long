/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salzghou <salzghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:26:19 by salzghou          #+#    #+#             */
/*   Updated: 2026/03/18 16:45:20 by salzghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	mlx_put_image_to_window(g->mlx, g->win, g->img.floor, x * 64, y * 64);
	if (g->map[y][x] == '1')
		mlx_put_image_to_window(g->mlx, g->win, g->img.wall, x * 64, y * 64);
	else if (g->map[y][x] == 'P')
		mlx_put_image_to_window(g->mlx, g->win, g->img.player, x * 64, y * 64);
	else if (g->map[y][x] == 'C')
		mlx_put_image_to_window(g->mlx, g->win, g->img.collectable, x * 64, y
			* 64);
	else if (g->map[y][x] == 'E')
		mlx_put_image_to_window(g->mlx, g->win, g->img.exit, x * 64, y * 64);
}
