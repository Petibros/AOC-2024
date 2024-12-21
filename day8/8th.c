#include "../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define SIZE 50

typedef struct s_coor
{
	int y;
	int x;
	struct s_coor *next;
} t_coor;

void    ft_lstadd_back(t_coor **lst, t_coor *new)
{
        t_coor  *addlast;

        if (!new || !lst)
                return ;
        addlast = *lst;
        if (*lst)
        {
                while (addlast->next)
                {
                        addlast = addlast->next;
                }
                addlast->next = new;
        }
        else
                *lst = new;
}

t_coor  *ft_lstnew(int y, int x)
{
        t_coor  *newnode;

        newnode = malloc(sizeof(t_coor));
        if (!newnode)
                return (NULL);
        newnode->y = y;
	newnode->x = x;
        newnode->next = NULL;
        return (newnode);
}

void	put_antinode(char **map, char c, t_coor **coor, int y, int x)
{
	int	i = 0;
	int	j;
	int	where_y;
	int	where_x;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == c && (i != y || j != x))
			{
				where_y = y + (y - i);
				where_x = x + (x - j);
				if (where_y < SIZE && where_x < ft_strnlen(map[i], '\n') && where_y >= 0 && where_x >= 0)
				{
					if (map[where_y][where_x] == '.' || map[where_y][where_x] == '#')
						map[where_y][where_x] = '#';
					else
						ft_lstadd_back(coor, ft_lstnew(where_y, where_x));
				}
			}
			++j;

		}
		++i;
	}
}

int	count(char **map)
{
	int	y = 0;
	int	x;
	int	count = 0;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '#')
				++count;
			++x;
		}
		++y;
	}
	return (count);
}

void	place_last_antinodes(t_coor *coor, char **map)
{
	while (coor)
	{
		map[coor->y][coor->x] = '#';
		coor = coor->next;
	}
}

int	get_antinodes(char **map)
{
	t_coor	*coor;
	int	y = 0;
	int	x;
	char	c;

	coor = NULL;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\n' && map[y][x])
		{
			if (map[y][x] != '.' && map[y][x] != '#')
			{
				c = map[y][x];
				put_antinode(map, c, &coor, y, x);
			}
			++x;
		}
		++y;
	}
	place_last_antinodes(coor, map);
	return (count(map));
}

int	main()
{
	int	i = 0;
	int	fd;
	int	res;
	char	*line;
	char	**file;

	res = 0;
	file = malloc(SIZE * sizeof(char *));
	fd = open("8th.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		file[i] = line;
		line = get_next_line(fd);
		++i;
	}
	file[i] = NULL;
	res = get_antinodes(file);
	i = 0;
	while (file[i])
	{
		printf("%s", file[i]);
		++i;
	}
	printf("%d", res);
	close(fd);
}
