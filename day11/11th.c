#include "../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct s_list
{
	size_t	content;
	struct s_list	*next;
}	t_list;

void    ft_lstadd_back(t_list **lst, t_list *new)
{
        t_list  *addlast;

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

t_list  *ft_lstnew(size_t content)
{
        t_list  *newnode;

        newnode = malloc(sizeof(t_list));
        if (!newnode)
                return (NULL);
        newnode->content = content;
        newnode->next = NULL;
        return (newnode);
}

int	num_len(size_t content)
{
	int	i = 0;

	while (content)
	{
		content /= 10;
		++i;
	}
	return (i);
}

int	ft_pow(int num, int times)
{
	int	res = 1;
	while (times)
	{
		res *= num;
		--times;
	}
	return (res);
}

void	split(t_list *nums)
{
	int	i = 0;
	int	limit = num_len(nums->content);
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->next = nums->next;
	nums->next = new;

	while (i < limit / 2)
	{
		new->content += (nums->content % 10) * ft_pow(10, i);
		nums->content /= 10;
		++i;
	}
}

size_t	apply_rules(t_list **list, size_t res)
{
	t_list	*nums;

	nums = *list;
	while (nums)
	{
		if (nums->content == 0)
			nums->content = 1;
		else if (num_len(nums->content) % 2 == 0)
		{
			split(nums);
			nums = nums->next->next;
			++res;
			continue ;
		}
		else
			nums->content *= 2024;
		nums = nums->next;
	}
	return (res);
}

int	main(int argc, char **argv)
{
	size_t	i = 1;
	t_list	*n;
	size_t	res = argc - 1;

	n = NULL;
	while (i < argc)
	{
		ft_lstadd_back(&n, ft_lstnew(atoi(argv[i])));
		++i;
	}
	i = 0;
	while (i < 25)
	{
		res = apply_rules(&n, res);
		++i;
	}
	printf("\n%zu", res);
}
