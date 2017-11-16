/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 15:00:45 by bviala            #+#    #+#             */
/*   Updated: 2017/08/11 15:12:01 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort(t_list **begin_list, int (*cmp)())
{
	t_list	*prev;
	t_list	*current;
	int		is_sort;

	is_sort = 1;
	while (is_sort--)
	{
		prev = NULL;
		current = *begin_list;
		while (current && current->next)
			if ((*cmp)(current->content, current->next->content) > 0)
			{
				(prev) ? prev->next = current->next : 0;
				(!prev) ? *begin_list = current->next : 0;
				prev = ft_lstswap(current);
				is_sort = 1;
			}
			else
			{
				prev = current;
				current = current->next;
			}
	}
}
