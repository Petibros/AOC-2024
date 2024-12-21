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

void	init_tab(int tab[8192][6], int y, int x, int size)
{
	tab[size][0] = y;
	tab[size][1] = x;
}

int	is_found(int y, int x, int coord[8192][2], int size)
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

void	erase_field(char **map, int coords[64][2], int area)
{
	int	i = 0;

	while (i < area)
	{
		map[coords[i][0]][coords[i][1]] = '.';
		++i;
	}
}

int	find_price(char **map, int y, int x, char c)
{
	int	area = 0;
	int	perimeter = 0;
	int	tab[8192][6];
	int	coords[8192][2];
	int	size = 0;
	int	valid[4];

	init_tab(tab, y, x, size);
	coords[area][0] = y;
	coords[area][1] = x;
	++area;
	perimeter += 4;
	if (y >= 1 && map[y - 1][x] == c)
              	--perimeter;
       	if (x >= 1 && map[y][x - 1] == c)
              	--perimeter;
       	if (ft_strnlen(map[y], '\n') - x >= 2 && map[y][x + 1] == c)
              	--perimeter;
        if (SIZE - y >= 2 && map[y + 1][x] == c)
              	--perimeter;
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
			coords[area][0] = y;
			coords[area][1] = x;
			++area;
			perimeter += 4;
			if (y >= 1 && map[y - 1][x] == c)
                        	--perimeter;
                	if (x >= 1 && map[y][x - 1] == c)
                        	--perimeter;
                	if (ft_strnlen(map[y], '\n') - x >= 2 && map[y][x + 1] == c)
                        	--perimeter;
                	if (SIZE - y >= 2 && map[y + 1][x] == c)
                        	--perimeter;
		}
	}
	erase_field(map, coords, area);
	return (area * perimeter);
}

void	print_map(char **map)
{
	int	i = 0;

	while (map[i])
	{
		printf("%s\n", map[i]);
		++i;
	}
	write(1, "\n", 1);
}

int	get_price(char **map)
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
				res += find_price(map, i, j, map[i][j]);
				print_map(map);
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

        res = 0;
        map = malloc(SIZE * sizeof(char *));
        fd = open("12th.txt", O_RDONLY);
        map[i] = get_next_line(fd);
        while (map[i])
        {
		++i;
                map[i] = get_next_line(fd);
        }
        res = get_price(map);
        printf("%d", res);
        close(fd);
}
