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

size_t	get_res(int *str, int size)
{
	size_t	i = 0;
	size_t	res = 0;

	while (i < size)
	{
		if (str[i] != -1)
		{
			res += i * str[i];
	//		++ID;
		}	
		++i;
	}
	return (res);
}

size_t	push_left(int *str, int size)
{
	size_t	i = 0;
	ssize_t	j = size - 1;
	size_t	count = 0;
	size_t	count_i = 0;
	int	copy = 0;
	int	num;

	while (j > 0)
	{
		if (copy == 1)
		{
			while (count > 0)
			{
				str[i] = str[j];
				str[j] = -1;
				--j;
				--count;
				++i;
			}
		}
		i = 0;
		copy = 0;
		j -= count;
		count = 1;
		count_i = 1;
		while (str[j] == -1)
			--j;
		num = str[j];
		while (str[j - count] == num)
			++count;
		while (str[i] != -1)
			 ++i;
		while (i < j)
		{
			while (str[i] != -1 && i < j)
				++i;
			while (str[i + count_i - 1] == -1)
			{
				if (count_i == count)
				{
					copy = 1;
					break ;
				}
				++count_i;
			}
			if (copy == 1)
				break ;
			i += count_i;
			count_i = 1;
		}
	}
	return (get_res(str, size));
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
	int	i = 0;
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
	while (i < count)
	{
		printf("%d", str[i]);
		++i;
	}
	printf("%zu", res);
	free(line);
	close(fd);
}
