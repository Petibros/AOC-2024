#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "../get_next_line/get_next_line.h"
#define SIZE 50

int	can_move(char **map, char move, int coords[2])
{
	int	i = 0;

	if (move == '^')
	{
		while (map[coords[0] - i - 1][coords[1]] == 'O')
			++i;
		if (map[coords[0] - i - 1][coords[1]] == '.')
			return (i);
	}
	if (move == '>')
	{
		while (map[coords[0]][coords[1] + i + 1] == 'O')
			++i;
		if (map[coords[0]][coords[1] + i + 1] == '.')
			return (i);
	}
	if (move == 'v')
	{
		while (map[coords[0] + i + 1][coords[1]] == 'O')
			++i;
		if (map[coords[0] + i + 1][coords[1]] == '.')
			return (i);
	}
	if (move == '<')
	{
		while (map[coords[0]][coords[1] - i - 1] == 'O')
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
		while (j < SIZE)
		{
			if (map[i][j] == 'O')
				res += (i * 100) + j;
			++j;
		}
		++i;
	}
	return (res);
}

/*void	print_map(char **map)
{
	int	i = 0;

	while (i < SIZE)
	{
		printf("%s", map[i]);
		++i;
	}
}*/

int	resolve(char **map, char *moves, int coords[2])
{
	int	i = 0;
	int	n;

	while (moves[i])
	{
		if (moves[i] == '^' && can_move(map, moves[i], coords) != -1)
		{
			n = can_move(map, moves[i], coords);
			while (n >= 0)
			{
				map[coords[0] - n - 1][coords[1]] = map[coords[0] - n][coords[1]];
				--n;
			}
			map[coords[0]][coords[1]] = '.';
			coords[0] -= 1;
		}
		else if (moves[i] == '>' && can_move(map, moves[i], coords) != -1)
		{
			n = can_move(map, moves[i], coords);
			while (n >= 0)
			{
				map[coords[0]][coords[1] + n + 1] = map[coords[0]][coords[1] + n];
				--n;
			}
			map[coords[0]][coords[1]] = '.';
			coords[1] += 1;	
		}
		else if (moves[i] == 'v' && can_move(map, moves[i], coords) != -1)
		{
			n = can_move(map, moves[i], coords);
			while (n >= 0)
			{
				map[coords[0] + n + 1][coords[1]] = map[coords[0] + n][coords[1]];
				--n;
			}
			map[coords[0]][coords[1]] = '.';
			coords[0] += 1;	
		}
		else if (moves[i] == '<' && can_move(map, moves[i], coords) != -1)
		{
			n = can_move(map, moves[i], coords);
			while (n >= 0)
			{
				map[coords[0]][coords[1] - n - 1] = map[coords[0]][coords[1] - n];
				--n;
			}
			map[coords[0]][coords[1]] = '.';
			coords[1] -= 1;		
		}
		++i;
//		print_map(map);
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
		while (j < SIZE)
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
		map[n] = get_next_line(fd);
		++n;
	}
	get_next_line(fd);
	moves = get_next_line(fd);
	get_coords(map, coords);
	res = resolve(map, moves, coords);
	printf("%d\n", res);
}
