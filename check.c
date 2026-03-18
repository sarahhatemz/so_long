/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salzghou <salzghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 15:52:27 by salzghou          #+#    #+#             */
/*   Updated: 2026/03/18 15:58:52 by salzghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_rec(t_game *game)
{
	size_t	fline;
	int		i;

	fline = ft_strlen(game->map[0]);
	game->width = (int)fline;
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

int	checkwalls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->width)
	{
		if (game->map[0][i] != '1' || game->map[game->height - 1][i] != '1')
			return (0);
		i++;
	}
	j = 0;
	while (j < game->height)
	{
		if (game->map[j][0] != '1' || game->map[j][game->width - 1] != '1')
			return (0);
		j++;
	}
	return (1);
}

static int	count_tile(t_game *game, int y, int x)
{
	char	c;

	c = game->map[y][x];
	if (c == 'P')
	{
		game->p_count++;
		game->px = x;
		game->py = y;
	}
	else if (c == 'E')
		game->e_count++;
	else if (c == 'C')
		game->c_count++;
	else if (c != '0' && c != '1')
		return (0);
	return (1);
}

int	check_chars(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (!count_tile(game, y, x))
				return (0);
			x++;
		}
		y++;
	}
	if (game->p_count != 1 || game->e_count != 1 || game->c_count < 1)
	{
		ft_printf("Error\n");
		ft_printf("Map must have exactly 1 P, 1 E, at least 1 C\n");
		return (0);
	}
	return (1);
}

char	**copy_map(t_game *game)
{
	char	**cpy;
	int		i;

	i = 0;
	cpy = malloc(sizeof(char *) * (game->height + 1));
	if (!cpy)
		return (NULL);
	while (i < game->height)
	{
		cpy[i] = ft_strdup(game->map[i]);
		if (!cpy[i])
		{
			free_pmap(cpy, i);
			return (NULL);
		}
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
