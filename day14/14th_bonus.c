#include "../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 500
#define Y 103
#define X 101

void	get_inputs(int	tab[4], char *line)
{
	int	i = 0;

	tab[0] = atoi(line + 2);
	while (line[i] != ',')
		++i;
	++i;
	tab[1] = atoi(line + i);
	while (line[i] != '=')
		++i;
	++i;
	tab[2] = atoi(line + i);
	while (line[i] != ',')
                ++i;
        ++i;
	tab[3] = atoi(line + i);
}

void	make_move(int tab[4], char map[Y][X + 1])
{
	tab[0] += tab[2];
	tab[1] += tab[3];
	if (tab[0] >= X)
		tab[0] -= X;
	if (tab[1] >= Y)
		tab[1] -= Y;
	if (tab[0] < 0)
		tab[0] += X;
	if (tab[1] < 0)
		tab[1] += Y;
	map[tab[1]][tab[0]] = '#';
}

void	print_map(char map[Y][X + 1])
{
	int	i = 0;

	while (i < Y)
	{
		printf("%s\n", map[i]);
		++i;
	}
}

void	reset_map(char map[Y][X + 1])
{
 	int     i = 0;
        int     j;

        while (i < Y)
        {
                j = 0;
                while (j < X)
                {
                        map[i][j] = '.';
                        ++j;
                }
                ++i;
        }
}

int	check_tree(char map[Y][X + 1])
{
	int	i = 0;
	int	j;

	while (i < Y)
	{
		j = 0;
		while (j < X)
		{
			if (j >= 5 && X - j >= 5 && Y - i >= 5 && map[i][j] == '#' && map[i + 1][j + 1] == '#' && map[i + 1][j - 1] == '#' && map[i + 2][j + 2] == '#' && map[i + 2][j - 2] == '#' && map[i + 3][j + 3] == '#' && map[i + 3][j - 3] == '#' && map[i + 4][j + 4] == '#' && map[i + 4][j - 4] == '#')
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}

void	resolve(int tab[SIZE][4], char map[Y][X + 1])
{
	int	i;
	int	n = 0;

	while (n < 10000)
	{
		i = 0;
		while (i < SIZE)
		{
			make_move(tab[i], map);
			++i;
		}
		++n;
		if (check_tree(map))
		{
			print_map(map);
			printf("%d\n", n);
		}
		reset_map(map);
	}
}

int	main()
{
	char	*line;
	int	fd;
	int	tab[SIZE][4];
	char	map[Y][X + 1];
	int	i = 0;
	int	j;

	while (i < Y)
	{
		j = 0;
		while (j < X)
		{
			map[i][j] = '.';
			++j;
		}
		map[i][j] = 0;
		++i;
	}
	i = 0;
	fd = open("14th.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		get_inputs(tab[i], line);
		free(line);
		line = get_next_line(fd);
		++i;
	}
	resolve(tab, map);
}
