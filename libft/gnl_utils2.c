/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salzghou <salzghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 16:42:45 by salzghou          #+#    #+#             */
/*   Updated: 2026/03/18 16:45:00 by salzghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*update(char *store)
{
	char	*nl;
	char	*new_store;

	if (!store)
		return (NULL);
	nl = ft_strchr(store, '\n');
	if (!nl)
	{
		free(store);
		return (NULL);
	}
	new_store = ft_strdup(nl + 1);
	free(store);
	if (!new_store || new_store[0] == '\0')
	{
		free(new_store);
		return (NULL);
	}
	return (new_store);
}

char	*linef(char *store)
{
	int		i;
	char	*line;

	if (!store || store[0] == '\0')
		return (NULL);
	i = 0;
	while (store[i] && store[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	ft_memcpy(line, store, i);
	if (store[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

int	join_free(char **store, char *buff)
{
	char	*tmp;

	tmp = ft_strjoin(*store, buff);
	free(*store);
	if (!tmp)
	{
		*store = NULL;
		return (1);
	}
	*store = tmp;
	return (0);
}

int	read_loop(int fd, char **store, char *buff, int *n)
{
	while (!ft_strchr(*store, '\n') && *n > 0)
	{
		*n = read(fd, buff, BUFFER_SIZE);
		if (*n < 0)
			return (1);
		buff[*n] = '\0';
		if (*n > 0 && join_free(store, buff))
			return (1);
	}
	return (0);
}

int	readjoin(int fd, char **store)
{
	char	*buff;
	int		n;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (1);
	n = 1;
	if (read_loop(fd, store, buff, &n))
	{
		free(buff);
		return (1);
	}
	free(buff);
	if (!*store || (*store)[0] == '\0')
		return (1);
	return (0);
}
