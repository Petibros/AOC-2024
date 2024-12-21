#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "../get_next_line/get_next_line.h"
#define SIZE 50

int	can_move(char **map, char move, int coords[2], int tab[512][2])
{
	int	i = 0;
	int	n = 0;
	int	x;

	if (move == '^')
	{
		while (true)
		{
			if (map[coords[0] - 1][tab[0][0]] == '[' || map[coords[0] - 1][coords[1]] == ']')
			{
				tab[n][1] = i;
				tab[n][0] = 
			}
			while (map[coords[0] - i - 1][tab[0][0]] == '[' || map[coords[0] - i - 1][coords[1]] == ']')
			{
				tab[0][0] = coords[1];
				tab[0][1] = i;
				++i;
			}
		}
	}
	if (move == '>')
	{
		while (map[coords[0]][coords[1] + i + 1] == '[' || map[coords[0]][coords[1] + i + 1] == ']')
			++i;
		if (map[coords[0]][coords[1] + i + 1] == '.')
			return (i);
	}
	if (move == 'v')
	{
		while (map[coords[0] + i + 1][coords[1]] == '[' || map[coords[0]][coords[1] + i + 1] == ']')
			++i;
		if (map[coords[0] + i + 1][coords[1]] == '.')
			return (i);
	}
	if (move == '<')
	{
		while (map[coords[0]][coords[1] - i - 1] == '[' || map[coords[0]][coords[1] + i + 1] == ']')
			++i;
		if (map[coords[0]][coords[1] - i - 1] == '.')
			return (i);
	}
	return (-1);
}

int	get_res(char **map)
{
	int	i = 0;
	int	j;
	int	res = 0;

	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE * 2)
		{
			if (map[i][j] == '[')
				res += (i * 100) + j;
			++j;
		}
		++i;
	}
	return (res);
}

void	print_map(char **map)
{
	int	i = 0;

	while (i < SIZE)
	{
		printf("%s", map[i]);
		++i;
	}
}

int	resolve(char **map, char *moves, int coords[2])
{
	int	i = 0;
	int	tab[512][2];
	int	n;

	while (moves[i])
	{
		if (moves[i] == '^' && can_move(map, moves[i], coords, tab) != -1)
		{
			n = can_move(map, moves[i], coords, tab);
			while (n >= 0)
			{
				map[coords[0] - n - 1][coords[1]] = map[coords[0] - n][coords[1]];
				--n;
			}
			map[coords[0]][coords[1]] = '.';
			coords[0] -= 1;
		}
		else if (moves[i] == '>' && can_move(map, moves[i], coords, tab) != -1)
		{
			n = can_move(map, moves[i], coords, tab);
			while (n >= 0)
			{
				map[coords[0]][coords[1] + n + 1] = map[coords[0]][coords[1] + n];
				--n;
			}
			map[coords[0]][coords[1]] = '.';
			coords[1] += 1;	
		}
		else if (moves[i] == 'v' && can_move(map, moves[i], coords, tab) != -1)
		{
			n = can_move(map, moves[i], coords, tab);
			while (n >= 0)
			{
				map[coords[0] + n + 1][coords[1]] = map[coords[0] + n][coords[1]];
				--n;
			}
			map[coords[0]][coords[1]] = '.';
			coords[0] += 1;	
		}
		else if (moves[i] == '<' && can_move(map, moves[i], coords, tab) != -1)
		{
			n = can_move(map, moves[i], coords, tab);
			while (n >= 0)
			{
				map[coords[0]][coords[1] - n - 1] = map[coords[0]][coords[1] - n];
				--n;
			}
			map[coords[0]][coords[1]] = '.';
			coords[1] -= 1;		
		}
		++i;
		print_map(map);
	}
	return (get_res(map));
}

void	get_coords(char **map, int coords[2])
{
	int	i = 0;
	int	j;

	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE * 2)
		{
			if (map[i][j] == '@')
			{
				coords[0] = i;
				coords[1] = j;
				return ;
			}
			++j;
		}
		++i;
	}
}

void	rearrange(char *map)
{
	int	n = SIZE;
	int	i;
	int	length = SIZE;

	while (n > 0)
	{
		i = length;
		while (i >= length - n)
		{
			map[i + 1] = map[i];
			--i;
		}
		if (map[i + 1] == '@')
			map[i + 2] = '.';
		if (map[i + 1] == 'O')
		{
			map[i + 1] = '[';
			map[i + 2] = ']';
		}
		--n;
		++length;
	}
}

int	main()
{
	int	fd;
	char	*moves;
	char	**map;
	int	n = 0;
	int	res;
	int	coords[2];

	fd = open("15th.txt", O_RDONLY);
	map = malloc(SIZE * sizeof(char *));
	while (n < SIZE)
	{
		map[n] = calloc(SIZE * 2 + 1, sizeof(char));
		++n;
	}
	n = 0;
	while (n < SIZE)
	{
		strcpy(map[n], get_next_line(fd));
		rearrange(map[n]);
		++n;
	}
	get_next_line(fd);
	moves = get_next_line(fd);
	get_coords(map, coords);
	res = resolve(map, moves, coords);
	printf("%d\n", res);
}
