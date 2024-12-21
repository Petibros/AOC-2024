#include "../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void	put_in_tab(int *str, int c, int n)
{
	int	i = 0;

	while (i < n)
	{
		str[i] = c;
		++i;
	}
}

void	transform_line(char *line, int *str)
{
	int	i = 0;
	int	ID = 0;
	size_t	j = 0;

	while (line[i] && line[i] != '\n')
	{
		if (i % 2 == 0)
		{
			put_in_tab(&str[j], ID, line[i] - 48);
			++ID;
			j += line[i] - 48;
		}
		else
		{
			put_in_tab(&str[j], -1, line[i] - 48);
			j += line[i] - 48;
		}
		++i;
	}
}

size_t	get_res(int *str)
{
	size_t	i = 0;
	size_t	res = 0;

	while (str[i] != -1)
	{
		res += i * str[i];
		++i;
	}
	return (res);
}

size_t	push_left(int *str, int size)
{
	size_t	i = 0;
	size_t	j = size - 1;

	while (str[j] == -1)
		--j;
	while (str[i] != -1)
		 ++i;
	while (i < j)
	{
		str[i] = str[j];
		str[j] = -1;
		while (str[j] == -1)
			--j;
		while (str[i] != -1)
			++i;
	}
	return (get_res(str));
}

size_t	get_count(char	*line)
{
	int	i = 0;
	size_t	count = 0;

	while (line[i] && line[i] != '\n')
	{
		count += line[i] - 48;
		++i;
	}
	return (count);
}

int	main()
{
	size_t	res = 0;
	char	*line;
	int	fd;
	int	*str;
	int	count;

	fd = open("9th.txt", O_RDONLY);
	line = get_next_line(fd);
	count = get_count(line);
	str = malloc(count * sizeof(int));
	transform_line(line, str);
	res = push_left(str, count);
	printf("%zu", res);
	free(line);
	close(fd);
}
