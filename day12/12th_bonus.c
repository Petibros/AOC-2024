#include "../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 140

int	check_valid(int valid[4])
{
	int	count = 0;
	int	i = 0;

	while (i < 4)
	{
		if (valid[i] == 1)
			++count;
		++i;
	}
	return (count);
}

void	init_tab(int tab[8192][2], int y, int x, int size)
{
	tab[size][0] = y;
	tab[size][1] = x;
}

int	is_found(int y, int x, int coord[8192][6], int size)
{
	int	i = 0;

	while (i < size)
	{
		if (coord[i][0] == y && coord[i][1] == x)
			return (1);
		++i;
	}
	return (0);
}

int	is_valid(int coords[6])
{
	int	n = 0;

	if (!coords[2] && !coords[3] && !coords[4] && !coords[5])
		return (4);
	if ((!coords[2] && !coords[3] && !coords[4]) || (!coords[3] && !coords[4] && !coords[5]) || (!coords[4] && !coords[5] && !coords[2]) || (!coords[5] && !coords[2] && !coords[3]))
		return (3);
	if ((!coords[2] && !coords[3]) || (!coords[3] && !coords[4]) || (!coords[4] && !coords[5]) || (!coords[5] && !coords[2]))
		return (2);
	return (n);
}

int	get_sides(char map[SIZE][SIZE], int coords[8192][6], int size)
{
	int	y = 0;
	int	x;
	int	corners = 0;

	while (y < size)
	{
		map[coords[y][0]][coords[y][1]] = 'O';
		if (is_valid(coords[y]) == 2)
			corners += 1;
		if (is_valid(coords[y]) == 3)
			corners += 2;
		if (is_valid(coords[y]) == 4)
			corners += 4;
		++y;
	}
	y = 0;
	while (y < SIZE)
	{
		x = 0;
		while (x < SIZE)
		{
			if (map[y][x] == 'O')
			{
				if (x >= 1 && SIZE - y >= 2 && map[y][x - 1] != 'O' && map[y + 1][x] == 'O' && map[y + 1][x - 1] == 'O')
					corners++;
				if (SIZE - x >= 2 && SIZE - y >= 2 && map[y][x + 1] != 'O' && map[y + 1][x + 1] == 'O' && map[y + 1][x] == 'O')
					corners++;
				if (SIZE - x >= 2 && SIZE - y >= 2 && map[y][x + 1] == 'O' && map[y + 1][x + 1] == 'O' && map[y + 1][x] != 'O')
					corners++;
				if (SIZE - x >= 2 && SIZE - y >= 2 && map[y + 1][x] == 'O' && map[y + 1][x + 1] != 'O' && map[y][x + 1] == 'O')
					corners++;
			}
			++x;
		}
		++y;
	}
	return (corners);
}

void	erase_field(char **map, int coords[8192][6], int area)
{
	int	i = 0;

	while (i < area)
	{
		map[coords[i][0]][coords[i][1]] = '.';
		++i;
	}
}

void	init_coords(int coords[6], int y, int x)
{
	coords[0] = y;
	coords[1] = x;
	coords[2] = 0;
	coords[3] = 0;
	coords[4] = 0;
	coords[5] = 0;
}

int	find_price(char **map, int y, int x, char c, char dup_map[SIZE][SIZE])
{
	int	area = 0;
	int	tab[8192][2];
	int	coords[8192][6];
	int	size = 0;
	int	valid[4];

	init_tab(tab, y, x, size);
	init_coords(coords[area], y, x);
	if (y >= 1 && map[y - 1][x] == c)
		coords[area][2] = 1;
	if (x >= 1 && map[y][x - 1] == c)
		coords[area][5] = 1;
	if (ft_strnlen(map[y], '\n') - x >= 2 && map[y][x + 1] == c)
		coords[area][3] = 1;
	if (SIZE - y >= 2 && map[y + 1][x] == c)
		coords[area][4] = 1;
	++area;
	while (size != -1)
	{
		valid[0] = 0;
		valid[1] = 0;
		valid[2] = 0;
		valid[3] = 0;
		if (y >= 1 && is_found(y - 1, x, coords, area) == 0 && map[y - 1][x] == c)
			valid[0] = 1;
		if (x >= 1 && is_found(y, x - 1, coords, area) == 0 && map[y][x - 1] == c)
			valid[1] = 1;
		if (ft_strnlen(map[y], '\n') - x >= 2 && is_found(y, x + 1, coords, area) == 0 && map[y][x + 1] == c)
			valid[2] = 1;
		if (SIZE - y >= 2 && is_found(y + 1, x, coords, area) == 0 && map[y + 1][x] == c)
			valid[3] = 1;
		if (check_valid(valid) == 0)
		{
			if (tab[size][0] == y && tab[size][1] == x)
				--size;
			if (size >= 0)
			{
				y = tab[size][0];
				x = tab[size][1];
			}
		}
		if (check_valid(valid) >= 2 && (tab[size][0] != y || tab[size][1] != x))
		{
			++size;
			init_tab(tab, y, x, size);
		}
		if (check_valid(valid) >= 1)
		{
			if (valid[0])	
				--y;
			else if (valid[1])
				--x;
			else if (valid[2])
				++x;
			else if (valid[3])
				++y;
			init_coords(coords[area], y, x);
			if (y >= 1 && map[y - 1][x] == c)
				coords[area][2] = 1;
			if (x >= 1 && map[y][x - 1] == c)
				coords[area][5] = 1;
			if (ft_strnlen(map[y], '\n') - x >= 2 && map[y][x + 1] == c)
				coords[area][3] = 1;
			if (SIZE - y >= 2 && map[y + 1][x] == c)
				coords[area][4] = 1;
			++area;
		}
	}
	erase_field(map, coords, area);
	return (area * get_sides(dup_map, coords, area));
}

void	reset_map(char map[SIZE][SIZE])
{
	int	i = 0;
	int	j;

	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			map[i][j] = 0;
			++j;
		}
		++i;
	}
}

int	get_price(char **map, char dup_map[SIZE][SIZE])
{
	int	i = 0;
	int	j;
	int	res = 0;

	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\n' && map[i][j])
		{
			if (map[i][j] != '.')
			{
				res += find_price(map, i, j, map[i][j], dup_map);
				reset_map(dup_map);
			}
			++j;
		}
		++i;
	}
	return (res);
}

int     main()
{
        int     i = 0;
        int     fd;
        int     res;
        char    **map;
	char	dup_map[SIZE][SIZE];

        res = 0;
        map = malloc(SIZE * sizeof(char *));
        fd = open("12th.txt", O_RDONLY);
        map[i] = get_next_line(fd);
        while (map[i])
        {
		++i;
                map[i] = get_next_line(fd);
        }
        res = get_price(map, dup_map);
        printf("%d", res);
        close(fd);
}
