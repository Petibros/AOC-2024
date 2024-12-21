#include "../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 41

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

void	init_tab(int tab[6], int y, int x)
{
	tab[0] = y;
	tab[1] = x;
	tab[2] = 0;
	tab[3] = 0;
	tab[4] = 0;
	tab[5] = 0;
}

int	can_go(int tab[6], int y, int x, int n)
{
	if (tab[0] == y && tab[1] == x && tab[n] == 0)
		return (1);
	if (tab[0] != y || tab[1] != x)
		return (1);
	return (0);
}

int	is_found(int found[256][2], int y, int x, int size)
{
	int	i = 0;

	while (i < size)
	{
		if (found[i][0] == y && found[i][1] == x)
			return (1);
		++i;
	}
	return (0);
}

int	find_trails(char **map, int y, int x)
{
	int	res = 0;
	int	tab[128][6];
	int	size = 0;
	int	valid[4];
	int	found[256][2];

	init_tab(tab[size], y, x);
	while (size != -1)
	{
		valid[0] = 0;
		valid[1] = 0;
		valid[2] = 0;
		valid[3] = 0;
		if (y >= 1 && can_go(tab[size], y, x, 2) && map[y - 1][x] == map[y][x] + 1)
			valid[0] = 1;
		if (x >= 1 && can_go(tab[size], y, x, 3) && map[y][x - 1] == map[y][x] + 1)
			valid[1] = 1;
		if (ft_strnlen(map[y], '\n') - x >= 2 && can_go(tab[size], y, x, 4) && map[y][x + 1] == map[y][x] + 1)
			valid[2] = 1;
		if (SIZE - y >= 2 && can_go(tab[size], y, x, 5) && map[y + 1][x] == map[y][x] + 1)
			valid[3] = 1;
		if (check_valid(valid) == 0 || map[y][x] == '9')
		{
			if (tab[size][0] == y && tab[size][1] == x)
				--size;
			if (map[y][x] == '9' && is_found(found, y, x, res) == 0)
			{
				found[res][0] = y;
				found[res][1] = x;
				++res;
			}
			if (size >= 0)
			{
				y = tab[size][0];
				x = tab[size][1];
			}
		}
		if (check_valid(valid) >= 2 && (tab[size][0] != y || tab[size][1] != x))
		{
			++size;
			init_tab(tab[size], y, x);
		}
		if (check_valid(valid) >= 1)
		{
			if (valid[0])
			{
				if (tab[size][0] == y && tab[size][1] == x)
					tab[size][2] = 1;
				--y;
			}
			else if (valid[1])
			{
				if (tab[size][0] == y && tab[size][1] == x)
					tab[size][3] = 1;
				--x;
			}
			else if (valid[2])
			{
				if (tab[size][0] == y && tab[size][1] == x)
					tab[size][4] = 1;
				++x;
			}
			else if (valid[3])
			{
				if (tab[size][0] == y && tab[size][1] == x)
					tab[size][5] = 1;
				++y;
			}
		}
	}
	return (res);
}

int	resolve(char **map)
{
	int	i = 0;
	int	j;
	int	res = 0;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
				res += find_trails(map, i, j);
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

        map = malloc(SIZE * sizeof(char *));
        fd = open("10th.txt", O_RDONLY);
        map[i] = get_next_line(fd);
        while (map[i])
        {
                ++i;
                map[i] = get_next_line(fd);
        }
        res = resolve(map);
        printf("%d", res);
}
