/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7th.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 08:07:43 by sacgarci          #+#    #+#             */
/*   Updated: 2024/12/07 11:10:21 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 850

int ft_pow(int num, int times);

size_t	concatenate(size_t	num, int to_c)
{
	int	n;
	int	to_push = 1;

	n = to_c;
	while (n >= 10)
	{
		n /= 10;
		to_push++;
	}
	to_push = ft_pow(10, to_push);
	num *= to_push;
	num += to_c;
	return (num);
}

char	*putnbr_base(int nbr, int base)
{
	int	i = 0;
	char	*comb;
	int	size = 0;
	int	nb = nbr;

	comb = calloc(32, sizeof(char));
	while (nb >= base)
	{
		size++;
		nb /= base;
	}
	while (nbr >= base)
	{
		comb[size - i] = (nbr % base) + 48;
		nbr /= base;
		++i;
	}
	comb[size - i] = nbr + 48;
	return (comb);
}

int	ft_pow(int num, int times)
{
	int	n;

	n = num;
	while (times > 1)
	{
		num *= n;
		--times;
	}
	return (num);
}

size_t	get_res(size_t num, int numbers[32], int size)
{
	size_t	res = numbers[0];
	int	i = 1;
	int	i_comb = 0;
	int	diff;
	int	pos_max;
	int	pos = 0;
	char *comb;

	pos_max = ft_pow(3, size - 1);
	if (pos_max == 1)
		pos_max++;
	while (pos < pos_max)
	{
		i = 1;
		i_comb = 0;
		res = numbers[0];
		comb = putnbr_base(pos, 3);
		if (size - 1 > strlen(comb))
		{
			diff = ((size - 1) - strlen(comb));
			while (diff > 0)
			{
				res += numbers[i];
				++i;
				--diff;
			}
		}
		while (comb[i_comb])
		{
			if (comb[i_comb] == '0')
				res += numbers[i];
			else if (comb[i_comb] == '1')
				res *= numbers[i];
			else if (comb[i_comb] == '2')
				res = concatenate(res, numbers[i]);
			++i;
			++i_comb;
		}
		if (res == num)
			return (num);
		++pos;
	}
	return (0);
}

int	get_size(int numbers[16])
{
	int	i = 0;

	while (numbers[i])
		++i;
	return (i);
}

size_t	resolve(size_t tab[SIZE], int numbers[SIZE][32])
{
	size_t	res = 0;
	int	i = 0;
	int	size;

	while(i < SIZE)
	{
		size = get_size(numbers[i]);
		res += get_res(tab[i], numbers[i], size);
		++i;
	}
	return (res);
}

void	get_numbers(int numbers[32], char *line)
{
	int	i = 0;
	int	j = 0;

	while (line[i])
	{
		if (line[i] == ' ')
		{
			numbers[j] = atoi(&line[i + 1]);
			++j;
		}
		++i;
	}
	numbers[j] = 0;
}

int	main()
{
	size_t	tab[SIZE];
	int	i = 0;
	int	fd;
	size_t	res;
	char	*line;
	int	numbers[SIZE][32];

	fd = open("7th.txt", O_RDONLY);	
	line = get_next_line(fd);
	while (line)
	{
		tab[i] = atoll(line);
		get_numbers(numbers[i], line);
		++i;
		free(line);
		line = get_next_line(fd);
	}
	res = resolve(tab, numbers);
	printf("%zu", res);
}
