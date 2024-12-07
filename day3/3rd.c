/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3rd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 08:24:04 by sacgarci          #+#    #+#             */
/*   Updated: 2024/12/07 11:09:07 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int	verif_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] < 47 || str[i] > 58)
        return (0);
	while (str[i] >= 47 && str[i] <= 58)
		i++;
	if (str[i] == ',')
		i++;
	else
		return (0);
	if (str[i] < 47 || str[i] > 58)
		return (0);
	while (str[i] >= 47 && str[i] <= 58)
		i++;
	if (str[i] == ')')
		i++;
	else
		return (0);
	return (1);
}

int	get_number(char *str)
{
	int	na;
	int	nb;

	na = atoi(str);
	while (*str >= 47 && *str <= 58)
		++str;
	nb = atoi(&str[1]);
	printf("%d : %d\n", na, nb);
	return (na * nb);
}

int	get_times(char *str)
{
	int	i;
	int	res;
	static int	to_do = 1;

	i = 0;
	res = 0;;
	while (str[i])
	{
		if (str[i] == 'd' && strncmp(&str[i], "do()", 4) == 0)
			to_do = 1;
		else if (str[i] == 'd' && strncmp(&str[i], "don\'t()", 7) == 0)
			to_do = 0;
		if (str[i] == 'm' && strncmp(&str[i], "mul(", 4) == 0 && verif_str(&str[i + 4]) && to_do == 1)
			res += get_number(&str[i + 4]);
		i++;
	}
	printf("%d\n", res);
	return (res);
}

int	main()
{
	int	res;
	int	fd;
	char	*line;

	res = 0;
	fd = open("3rd.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		res += get_times(line);
		free(line);
		line = get_next_line(fd);
	}
	printf("%d", res);
	close(fd);
}
