/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6th_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 08:52:41 by sacgarci          #+#    #+#             */
/*   Updated: 2024/12/07 11:09:59 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int	resolve(char **map, int pos[2])
{
	int	x;
	int	y;
	int	direction[4];
	int	count = 0;

	direction[0] = 1;
	direction[1] = 0;
	direction[2] = 0;
	direction[3] = 0;
	x = pos[1];
	y = pos[0];
	while (y >= 0 && y < 130 && x >= 0 && x < 130)
	{
		while (map[y][x] != '#' && map[y][x] != '\n' && map[y][x])
		{
			++count;
			if (count > 10000)
				return (1);
			if (direction[0])
				--y;
			else if (direction[1])
				++x;
			else if (direction[2])
				++y;
			else if (direction[3])
				--x;
			if (y < 0 || y >= 130 || x < 0 || x >= 130)
				return (0);
		}
		if (direction[0])
        {
			direction[0] = 0;
			direction[1] = 1;
			++y;
			++x;
		}
        else if (direction[1])
        {
			direction[1] = 0;
			direction[2] = 1;
			--x;
			++y;
		}
        else if (direction[2])
        {
			direction[2] = 0;
			direction[3] = 1;
			--y;
			--x;
		}
        else if (direction[3])
        {
			direction[3] = 0;
			direction[0] = 1;
			++x;
			--y;
		}
	}
	return (0);
}

void	find_guard(char **map, int tab[2])
{
	int	x;
	int	y = 0;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '^')
			{
				tab[0] = y;
				tab[1] = x;
				return ;
			}
			++x;
		}
		++y;
	}
}

int	main()
{
	int	tab[2];
	int	i = 0;
	int	fd;
	int	res = 0;
	int	x = 0;
	int	y = 0;
	char	**map;

	map = malloc(130 * sizeof(char *));
	fd = open("6th.txt", O_RDONLY);	
	map[i] = get_next_line(fd);
	while (map[i])
	{
		++i;
		map[i] = get_next_line(fd);
	}
	find_guard(map, tab);
	while (y < 130)
	{
		x = 0;
		while (x < 130)
		{
			if (map[y][x] == '.')
			{
				map[y][x] = '#';
				res += resolve(map, tab);
				map[y][x] = '.';
			}
			++x;
		}
		++y;
	}
	printf("%d", res);
}
