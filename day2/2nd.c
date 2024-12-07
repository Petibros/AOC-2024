/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2nd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 09:33:42 by sacgarci          #+#    #+#             */
/*   Updated: 2024/12/07 11:08:57 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	descending_verif(int *tab, int size);
int ascending_verif(int *tab, int size);

void	remove_from(int	*tab, int index, int size)
{
	while (index + 1 < size)
	{
		tab[index] = tab[index + 1];
		index++;
	}
}

void	fill_dup(int *tab, int *dup_tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dup_tab[i] = tab[i];
		i++;
	}
}

int	test_remove(int	*tab, int size)
{
	int	i;
	int	*dup_tab;

	dup_tab = malloc(size * sizeof(int));
	i = 0;
	while (i < size)
	{
		fill_dup(tab, dup_tab, size);
		remove_from(dup_tab, i, size);
		if (dup_tab[0] < dup_tab[1])
   	 	{
       		if (ascending_verif(dup_tab, size - 1))
           		return (1);
    	}
   		else
    	{
       		if (descending_verif(dup_tab, size - 1))
            	return (1);
    	}
		i++;
	}
	return (0);
}

int	descending_verif(int *tab, int size)
{
	int	i;

	i = 1;
	while (i < size)
	{
		if (tab[i - 1] - tab[i] >= 4 || tab[i - 1] - tab[i] <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	ascending_verif(int	*tab, int size)
{
	int	i;

	i = 1;
	while (i < size)
	{
		if (tab[i] - tab[i - 1] >= 4 || tab[i] - tab[i - 1] <= 0)
			return (0);
		i++;
	}
	return (1);
}

int	verif(char *line)
{
	int	tab[12];
	int	i;
	int	i_tab;

	i = 0;
	i_tab = 0;
	while (line[i] && line[i] != '\n')
	{
		tab[i_tab] = atoi(&line[i]);
		i_tab++;
		while (line[i] >= '0' && line[i] <= '9')
			i++;
		if (line[i] == ' ')
			i++;
	}
	if (tab[0] < tab[1])
	{
		if (ascending_verif(tab, i_tab))
			return (1);
		else if (test_remove(tab, i_tab))
			return (1);
	}
	else
	{
		if (descending_verif(tab, i_tab))
			return (1);
		else if (test_remove(tab, i_tab))
			return (1);
	}
	return (0);
}

int	main()
{
	int	safe_counter;
	int	fd;
	char	*line;

	safe_counter = 0;
	fd = open("2nd.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		safe_counter += verif(line);
		free(line);
		line = get_next_line(fd);
	}
	printf("%d", safe_counter);
	close(fd);
}
