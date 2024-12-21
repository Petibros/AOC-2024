#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include "../get_next_line/get_next_line.h"
#define SIZE 320

typedef struct s_struct
{
	ssize_t b_A[512][2];
	ssize_t	b_B[512][2];
	ssize_t	prize[512][2];
} t_arcade;

ssize_t	absolue(ssize_t a, ssize_t b)
{
	if (a > b)
		return (a - b);
	return (b - a);
}

size_t	get_price(ssize_t tab_A[2], ssize_t tab_B[2], ssize_t tab_prize[2])
{
	ssize_t	x;
	ssize_t	y;

	y = ((tab_prize[1] * tab_A[0] * -1) + (tab_A[1] * tab_prize[0])) / ((tab_A[0] * tab_B[1] * -1) + (tab_A[1] * tab_B[0]));
	x = (tab_prize[0] - (tab_B[0] * y)) / tab_A[0];
	if (((tab_prize[1] * tab_A[0] * -1) + (tab_A[1] * tab_prize[0])) % ((tab_A[0] * tab_B[1] * -1) + (tab_A[1] * tab_B[0])) != 0 || (tab_prize[0] - (tab_B[0] * y)) % tab_A[0] != 0)
		return (0);
	return ((x * 3) + y);
}

size_t	resolve(t_arcade *arcades)
{
	size_t	res = 0;
	int	n = 0;

	while (n < SIZE)
	{
		res += get_price(arcades->b_A[n], arcades->b_B[n], arcades->prize[n]);
		++n;
	}
	return (res);
}

void	get_inputs(char *line, ssize_t tab[512][2], int n)
{
	int	i = 0;

	while (line[i] != 'X')
		++i;
	tab[n][0] = atoi(&line[i + 2]);
	while (line[i] != 'Y')
		++i;
	tab[n][1] = atoi(&line[i + 2]);
}

int	main()
{
	int		fd;
	char		*line;
	t_arcade	*arcades;
	int	i = 0;
	size_t	res = 0;

	arcades = malloc(sizeof(t_arcade));
	fd = open("13th.txt", O_RDONLY);
	while (i < SIZE)
	{
		line = get_next_line(fd);
		get_inputs(line, arcades->b_A, i);
		line = get_next_line(fd);
		get_inputs(line, arcades->b_B, i);	
		line = get_next_line(fd);
		get_inputs(line, arcades->prize, i);
		arcades->prize[i][0] += 10000000000000;
		arcades->prize[i][1] += 10000000000000;
		++i;
		line = get_next_line(fd);
	}
	res = resolve(arcades);
	printf("%zu", res);
}
