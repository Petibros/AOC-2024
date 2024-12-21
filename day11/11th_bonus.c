#include "../get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_list
{
	size_t	content;
	size_t	stocked;
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
	newnode->stocked = 1;
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

bool	is_existing(t_list *num, t_list **list)
{
	t_list	*travel;

	travel = *list;
	while (travel != num)
	{
		if (travel->content == num->content)
		{
			travel->stocked += num->stocked;
			return (true);
		}
		travel = travel->next;
	}
	return (false);
}

void	split(t_list *nums)
{
	int	i = 0;
	int	limit = num_len(nums->content);
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->stocked = nums->stocked;
	new->content = 0;
	new->next = nums->next;
	nums->next = new;

	while (i < limit / 2)
	{
		new->content += (nums->content % 10) * ft_pow(10, i);
		nums->content /= 10;
		++i;
	}
}

void	delone(t_list *list)
{
	t_list *saved;

	saved = list->next->next;
	free(list->next);
	list->next = saved;
}

size_t	apply_rules(t_list **list, size_t res)
{
	t_list	*nums;
	t_list	*saved;

	nums = malloc(sizeof(t_list));
	nums->next = *list;
	while (nums->next)
	{
		if (nums->next->content == 0)
			nums->next->content = 1;
		else if (num_len(nums->next->content) % 2 == 0)
		{
			split(nums->next);
			res += nums->next->stocked;
			if (is_existing(nums->next, list))
				delone(nums);
			else
				nums = nums->next;
			if (is_existing(nums->next, list))
				delone(nums);
			else
				nums = nums->next;
			continue ;

		}
		else
			nums->next->content *= 2024;
		if (is_existing(nums->next, list))
		{
			delone(nums);
			continue ;
		}
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
	while (i < 75)
	{
		res = apply_rules(&n, res);
		++i;
	}
	printf("\n%zu", res);
}
