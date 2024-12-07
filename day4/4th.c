/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4th.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 07:25:41 by sacgarci          #+#    #+#             */
/*   Updated: 2024/12/07 11:09:32 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int	get_hor(char **file)
{
	int	i;
	int	res = 0;
	int	j = 0;

	while (file[j])
	{
		i = 0;
		while (file[j][i])
		{
			if (file[j][i] == 'S' && strncmp(&file[j][i], "SAMX", 4) == 0)
				res++;
			if (file[j][i] == 'X' && strncmp(&file[j][i], "XMAS", 4) == 0)
				res++;
			i++;
		}
		j++;
	}
	return (res);
}

int	get_ver(char **file)
{
	int	res = 0;
	int	j = 0;
	int	i;

	while (j < 140)
	{
		i = 0;
		while (file[j][i])
		{
			if (j >= 3 && file[j][i] == 'X' && file[j - 1][i] == 'M' && file[j - 2][i] == 'A' && file[j - 3][i] == 'S')
				res++;
			if (139 - j >= 3 && file[j][i] == 'X' && file[j + 1][i] == 'M' && file[j + 2][i] == 'A' && file[j + 3][i] == 'S')
				res++;
			i++;
		}
		j++;
	}
	return (res);
}

int	get_diag(char **file)
{
	int	res = 0;
	int	j = 0;
	int	i;

	while (j < 140)
	{
		i = 0;
		while (file[j][i])
		{
			if (j >= 3 && i >= 3 && file[j][i] == 'X' && file[j - 1][i - 1] == 'M' && file[j - 2][i - 2] == 'A' && file[j - 3][i - 3] == 'S')
				res++;
			if (j >= 3 && strlen(file[j]) - i >= 4 && file[j][i] == 'X' && file[j - 1][i + 1] == 'M' && file[j - 2][i + 2] == 'A' && file[j - 3][i + 3] == 'S')
				res++;
			if (139 - j >= 3 && i >= 3 && file[j][i] == 'X' && file[j + 1][i - 1] == 'M' && file[j + 2][i - 2] == 'A' && file[j + 3][i - 3] == 'S')
				res++;
			if (139 - j >= 3 && strlen(file[j]) - i >= 4 && file[j][i] == 'X' && file[j + 1][i + 1] == 'M' && file[j + 2][i + 2] == 'A' && file[j + 3][i + 3] == 'S')
				res++;
			i++;
		}
		j++;
	}
	return (res);
}

int	get_XMAS(char **file)
{
	int	res;

	res = get_hor(file);
	res += get_ver(file);
	res += get_diag(file);
	return (res);
}

int	main()
{
	int	i = 0;
	int	fd;
	int	res;
	char	*line;
	char	**file;

	res = 0;
	file = malloc(140 * sizeof(char *));
	fd = open("4th.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		file[i] = line;
		line = get_next_line(fd);
		++i;
	}
	file[i] = NULL;
	res = get_XMAS(file);
	printf("%d", res);
	close(fd);
}
