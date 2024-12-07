/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5th.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 07:54:28 by sacgarci          #+#    #+#             */
/*   Updated: 2024/12/07 11:09:42 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int	*malloc_tab(char *line)
{
	int	*tab;
	int	i = 0;
	int	j = 0;

	tab = malloc(100 * sizeof(int));
	i = 1;
	tab[0] = atoi(line);
	while (line[j])
	{
		if (line[j] == ',')
		{
			tab[i] = atoi(&line[j + 1]);
			i++;
		}
		++j;
	}
	return (tab);
}

int	order(int *tab, int rules[1176][2], int size)
{
	int	j = 0;
	int	i;
	int	saved_1;
	int	saved_2;
	int	tmp;

	while (j < 1176)
    {
        i = 0;
        saved_1 = -1;
        saved_2 = -1;
        while (i < size)
        {
            if (tab[i] == rules[j][0])
                saved_1 = i;
            else if (tab[i] == rules[j][1])
                saved_2 = i;
            ++i;
        }
        if (saved_1 != -1 && saved_2 != -1 && saved_2 < saved_1)
        {
			tmp = tab[saved_1];
			tab[saved_1] = tab[saved_2];
			tab[saved_2] = tmp;
            j = 0;
			continue ;
        }
        ++j;
    }
	if (size % 2)
		return (tab[size / 2]);
	return (tab[(size / 2) - 1]);
}

int	get_number(char *line, int rules[1176][2])
{
	int	*tab;
	int	middle;
	int	size = 1;
	int	i = 0;
	int	j = 0;
	int	saved_1 = -1;
	int	saved_2 = -1;

	tab = malloc_tab(line);
	while (line[i])
	{
		if (line[i] == ',')
			++size;
		++i;
	}
	i = 0;
	while (j < 1176)
	{
		i = 0;
		saved_1 = -1;
		saved_2 = -1;
		while (i < size)
		{
			if (tab[i] == rules[j][0])
				saved_1 = i;
			else if (tab[i] == rules[j][1])
				saved_2 = i;
			++i;
		}
		if (saved_1 != -1 && saved_2 != -1 && saved_2 < saved_1)
		{
			middle = order(tab, rules, size);
			free(tab);
			return (middle);
		}
		++j;
	}
	return (0);
}

int	main()
{
	int	i = 0;
	int	fd_rules;
	int	fd_updates;
	int	res;
	char	*line;
	int	rules[1176][2];

	res = 0;
	fd_rules = open("5th.txt", O_RDONLY);
	fd_updates = open("5thupdates.txt", O_RDONLY);
	line = get_next_line(fd_rules);
	while (line)
	{
		rules[i][0] = atoi(line);
		rules[i][1] = atoi(&line[3]);
		free(line);
		++i;
		line = get_next_line(fd_rules);
	}
	i = 0;
	line = get_next_line(fd_updates);
	while (line)
	{
		res += get_number(line, rules);
		free(line);
		line = get_next_line(fd_updates);
	}
	printf("%d", res);
	close(fd_rules);
	close(fd_updates);
}
