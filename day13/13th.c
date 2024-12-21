#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include "../get_next_line/get_next_line.h"
#define SIZE 320

typedef struct s_struct
{
	int	b_A[512][2];
	int	b_B[512][2];
	int	prize[512][2];
} t_arcade;

int	get_price(int tab_A[2], int tab_B[2], int tab_prize[2])
{
	int	total_price = 0;
	int	saved_price = 0;
	int	total_X = 0;
	int	total_Y = 0;

	while (total_X < tab_prize[0] && total_Y < tab_prize[1] && total_price / 3 <= 100)
	{
		total_X += tab_A[0];
		total_Y += tab_A[1];
		total_price += 3;
	}
	while (total_X >= 0 && total_Y >= 0)
	{
		if ((tab_prize[0] - total_X) % tab_B[0] == 0 && (tab_prize[1] - total_Y) % tab_B[1] == 0 && (tab_prize[1] - total_Y) / tab_B[1] == (tab_prize[0] - total_X) / tab_B[0])
		{
			total_price += (tab_prize[1] - total_Y) / tab_B[1];
			if (saved_price == 0 || total_price < saved_price)
				saved_price = total_price;
		}
		total_X -= tab_A[0];
		total_Y -= tab_A[1];
		total_price -= 3;
	}
	return (saved_price);
}

int	resolve(t_arcade *arcades)
{
	int	res = 0;
	int	n = 0;

	while (n < SIZE)
	{
		res += get_price(arcades->b_A[n], arcades->b_B[n], arcades->prize[n]);
		++n;
	}
	return (res);
}

void	get_inputs(char *line, int tab[512][2], int n)
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
	int	res = 0;

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
		++i;
		line = get_next_line(fd);
	}
	res = resolve(arcades);
	printf("%d", res);
}
