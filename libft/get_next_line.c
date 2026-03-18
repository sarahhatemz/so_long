/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salzghou <salzghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:04:40 by salzghou          #+#    #+#             */
/*   Updated: 2026/03/18 16:44:02 by salzghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!store)
		store = ft_strdup("");
	if (!store)
		return (NULL);
	if (readjoin(fd, &store))
	{
		free(store);
		store = NULL;
		return (NULL);
	}
	line = linef(store);
	if (!line)
	{
		free(store);
		store = NULL;
		return (NULL);
	}
	store = update(store);
	return (line);
}
