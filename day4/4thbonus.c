/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4thbonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 07:25:41 by sacgarci          #+#    #+#             */
/*   Updated: 2024/12/07 11:09:22 by sacgarci         ###   ########.fr       */
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
			if (139 - j >= 2 && strlen(file[j]) - i >= 3 && file[j][i] == 'M' && file[j][i + 2] == 'M' && file[j + 1][i + 1] == 'A' && file[j + 2][i] == 'S' && file[j + 2][i + 2] == 'S')
				res++;
			if (j >= 2 && strlen(file[j]) - i >= 3 && file[j][i] == 'M' && file[j][i + 2] == 'M' && file[j - 1][i + 1] == 'A' && file[j - 2][i] == 'S' && file[j - 2][i + 2] == 'S')
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
			if (139 - j >= 2 && strlen(file[j]) - i >= 3 && file[j][i] == 'M' && file[j + 2][i] == 'M' && file[j + 1][i + 1] == 'A' && file[j + 2][i + 2] == 'S' && file[j][i + 2] == 'S')
				res++;
			if (139 - j >= 2 && i >= 2 && file[j][i] == 'M' && file[j + 2][i] == 'M' && file[j + 1][i - 1] == 'A' && file[j + 2][i - 2] == 'S' && file[j][i - 2] == 'S')
				res++;
			i++;
		}
		j++;
	}
	return (res);
}

int	get_MAS(char **file)
{
	int	res;

	res = get_hor(file);
	res += get_ver(file);
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
	res = get_MAS(file);
	printf("%d", res);
	close(fd);
}
