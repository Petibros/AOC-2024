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

void	make_move(int tab[4])
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
}

int	place_robots(int tab[SIZE][4])
{
	int	i = 0;
	int	one = 0;
	int	two = 0;
	int	three = 0;
	int	four = 0;

	while (i < SIZE)
	{
		if (tab[i][0] < X / 2 && tab[i][1] < Y / 2)
			++one;
		if (tab[i][0] > X / 2 && tab[i][1] < Y / 2)
			++two;
		if (tab[i][0] < X / 2 && tab[i][1] > Y / 2)
			++three;
		if (tab[i][0] > X / 2 && tab[i][1] > Y / 2)
			++four;
		++i;
	}
	return (one * two * three * four);
}

int	resolve(int tab[SIZE][4])
{
	int	i;
	int	n = 0;

	while (n < 100)
	{
		i = 0;
		while (i < SIZE)
		{
			make_move(tab[i]);
			++i;
		}
		++n;
	}
	return (place_robots(tab));
}

int	main()
{
	char	*line;
	int	fd;
	int	tab[SIZE][4];
	int	i = 0;
	int	j;
	int	res;

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
	res = resolve(tab);
	printf("%d\n", res);
}
