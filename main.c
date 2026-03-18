/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salzghou <salzghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:20:03 by salzghou          #+#    #+#             */
/*   Updated: 2026/03/18 17:15:37 by salzghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	checks(t_game *game)
{
	if (!check_rec(game))
	{
		free_pmap(game->map, game->height);
		exit(1);
	}
	if (!checkwalls(game))
	{
		ft_printf("Error\nMap is not closed by walls\n");
		free_pmap(game->map, game->height);
		exit(1);
	}
	if (!check_chars(game))
	{
		free_pmap(game->map, game->height);
		exit(1);
	}
	if (!validation(game))
	{
		ft_printf("Error\nNo valid path in map\n");
		free_pmap(game->map, game->height);
		exit(1);
	}
}

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./so_long <map.ber>\n");
		return (1);
	}
	init_game(&game);
	if (!storing_map(&game, argv[1]))
	{
		return (1);
	}
	checks(&game);
	if (!init_window(&game))
	{
		free_pmap(game.map, game.height);
		return (1);
	}
	if (!load_images(&game))
	{
		close_hook(&game);
		return (1);
	}
	draw_map(&game);
	mlx_hook(game.win, 2, 1L << 0, key_hook, &game);
	mlx_hook(game.win, 17, 0, close_hook, &game);
	mlx_loop(game.mlx);
}
