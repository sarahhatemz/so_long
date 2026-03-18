/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salzghou <salzghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:16:12 by salzghou          #+#    #+#             */
/*   Updated: 2026/03/18 18:15:37 by salzghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_map(t_game *g)
{
	int	y;
	int	x;

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

int	close_hook(t_game *g)
{
	if (g->img.wall)
		mlx_destroy_image(g->mlx, g->img.wall);
	if (g->img.floor)
		mlx_destroy_image(g->mlx, g->img.floor);
	if (g->img.player)
		mlx_destroy_image(g->mlx, g->img.player);
	if (g->img.collectable)
		mlx_destroy_image(g->mlx, g->img.collectable);
	if (g->img.exit)
		mlx_destroy_image(g->mlx, g->img.exit);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	free(g->mlx);
	if (g->map)
		free_pmap(g->map, g->height);
	exit(0);
	return (0);
}

static void	update_pos(t_game *g, int nx, int ny, char t)
{
	if (t == 'C')
	{
		g->c_count--;
		g->map[ny][nx] = '0';
	}
	if (g->ey != g->py || g->ex != g->px)
		g->map[g->py][g->px] = '0';
	g->px = nx;
	g->py = ny;
	g->map[g->py][g->px] = 'P';
	g->moves++;
	ft_printf("Moves: %d\n", g->moves);
	draw_map(g);
	if (g->ey == ny && g->ex == nx)
		g->map[g->ey][g->ex] = 'E';
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
	if (t == 'E' && g->c_count == 0)
	{
		g->moves++;
		ft_printf("Moves: %d\n", g->moves);
		ft_printf("You won in %d moves!\n", g->moves);
		close_hook(g);
	}
	update_pos(g, nx, ny, t);
}

int	key_hook(int keycode, t_game *g)
{
	if (keycode == 65307)
		close_hook(g);
	else if (keycode == 'w' || keycode == 119 || keycode == 65362)
		try_move(g, 0, -1);
	else if (keycode == 's' || keycode == 115 || keycode == 65364)
		try_move(g, 0, 1);
	else if (keycode == 'a' || keycode == 97 || keycode == 65361)
		try_move(g, -1, 0);
	else if (keycode == 'd' || keycode == 100 || keycode == 65363)
		try_move(g, 1, 0);
	return (0);
}
