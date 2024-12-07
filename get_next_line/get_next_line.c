/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:06:25 by sacgarci          #+#    #+#             */
/*   Updated: 2024/11/09 17:11:28 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int	join_and_free(char **rest, char *buffer)
{
	char	*tmp;

	tmp = ft_calloc(1 + ft_strnlen(*rest, '\0'), sizeof(char));
	if (!tmp)
	{
		free(buffer);
		buffer = NULL;
		free(*rest);
		free(rest);
		return (0);
	}
	ft_strcpy(tmp, *rest);
	free(*rest);
	*rest = ft_strjoin(tmp, buffer);
	if (!*rest)
	{
		free(*rest);
		free(rest);
		free(buffer);
		buffer = NULL;
		return (0);
	}
	free(tmp);
	return (1);
}

static char	*get_line(char *rest, char *buffer)
{
	char	*line;
	int		i;

	if (!rest[0])
		return (NULL);
	i = 0;
	line = ft_calloc((2 + ft_strnlen(rest, '\n')), sizeof(char));
	if (!line)
		return (NULL);
	while (rest[i] && rest[i] != '\n')
	{
		line[i] = rest[i];
		i++;
	}
	if (rest[i] == '\n')
		line[i] = '\n';
	i = ft_strnlen(buffer, '\n');
	if (buffer[i] == '\n')
		i++;
	ft_strcpy(buffer, &buffer[i]);
	return (line);
}

static int	read_line(char *buffer, char **rest, int fd)
{
	int	has_read;

	has_read = 1;
	while (has_read)
	{
		if (!join_and_free(rest, buffer))
			return (0);
		if (ft_strchr(buffer, '\n'))
			break ;
		has_read = read(fd, buffer, BUFFER_SIZE);
		if (has_read == -1)
			return (0);
		buffer[has_read] = '\0';
	}
	return (1);
}

static char	*initialize(char *buffer, int fd)
{
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!buffer)
		buffer = ft_calloc(1 + BUFFER_SIZE, sizeof(char));
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		**rest;
	char		*line;

	line = NULL;
	buffer = initialize(buffer, fd);
	if (!buffer)
		return (NULL);
	rest = malloc(1 * sizeof(char *));
	*rest = ft_calloc(1, sizeof(char));
	if (!*rest)
		return (NULL);
	if (read_line(buffer, rest, fd))
		line = get_line(*rest, buffer);
	free(*rest);
	free(rest);
	if (line)
		return (line);
	free(buffer);
	buffer = NULL;
	return (NULL);
}

