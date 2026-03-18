/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salzghou <salzghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:24:39 by salzghou          #+#    #+#             */
/*   Updated: 2026/03/18 16:26:00 by salzghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	open_map(char *mapname)
{
	int	fd;
	int	len;

	len = ft_strlen(mapname);
	if (len < 5 || mapname[len - 4] != '.' || mapname[len - 3] != 'b'
		|| mapname[len - 2] != 'e' || mapname[len - 1] != 'r')
	{
		ft_printf("Error\nInvalid map extension\n");
		return (-1);
	}
	fd = open(mapname, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nFailed to open map\n");
		return (-1);
	}
	return (fd);
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

int	map_height(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	if (!line)
		return (0);
	while ((line))
	{
		line = get_next_line(fd);
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
