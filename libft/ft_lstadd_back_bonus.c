/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:38:00 by sacgarci          #+#    #+#             */
/*   Updated: 2024/10/14 21:35:15 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*addlast;

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
