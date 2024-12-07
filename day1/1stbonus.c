/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1stbonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 09:01:59 by sacgarci          #+#    #+#             */
/*   Updated: 2024/12/01 09:06:43 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	*fill_tab_b(char **input)
{
	int	i;
	int	j;
	int	k;
	int	*tab_b;

	i = 0;
	k = 0;
	tab_b = malloc(2000 * sizeof(int));
	while (input[i])
	{
		j = 0;
		while (input[i][j])
		{
			if (input[i][j] == ' ')
			{
				j += 3;
				tab_b[k] = atoi(&input[i][j]);
				k++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (tab_b);
}

int	*fill_tab_a(char **input)
{
	int	i;
	int	j;
	int	*tab_a;

	i = 0;
	j = 0;
	tab_a = malloc(2000 * sizeof(int));
	while (input[i])
	{
		tab_a[j] = atoi(&input[i][0]);
		j++;
		i++;
	}
	return (tab_a);
}

int	get_times(int *tab, int num)
{
	int	times;
	int	i;

	i = 0;
	times = 0;
	while (i < 1000)
	{
		if (tab[i] == num)
			times++;
		i++;
	}
	return (times);
}

int	compare(int *tab_a, int *tab_b)
{
	int	times;
	int	result;
	int	n;
	int	num;

	result = 0;
	n = 0;
	while (n < 1000)
	{
		num = tab_a[n];
		times = get_times(tab_b, num);
		result += times * num;
		n++;
	}
	return (result);
}

int	main(int argc, char **argv)
{
	int	*tab_a;
	int	*tab_b;
	int	result;
	(void) argc;

	tab_a = fill_tab_a(&argv[1]);
	tab_b = fill_tab_b(&argv[1]);
	result = compare(tab_a, tab_b);
	printf("%d", result);
}
