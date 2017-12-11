/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_insert_sort.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 19:08:54 by bviala            #+#    #+#             */
/*   Updated: 2017/11/15 17:06:03 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	insert_sort(t_ldl_head *ldl, t_ldl *new, t_ldl *curr, int (*fcmp)())
{
	while (curr && fcmp(curr->content, new->content) < 0)
		curr = curr->next;
	if (curr)
	{
		if (!curr->prev)
			ldl->head = new;
		else
		{
			curr->prev->next = new;
			new->prev = curr->prev;
		}
		new->next = curr;
		curr->prev = new;
	}
	else
	{
		new->prev = ldl->tail;
		if (ldl->tail)
			ldl->tail->next = new;
		ldl->tail = new;
	}
}

t_ldl_head	*ft_ldl_insert_sort(t_ldl_head *ldl, t_ldl *new, int (*fcmp)())
{
	t_ldl	*curr;

	if (!ldl || !new)
		return (ldl);
	if (!(curr = ldl->head))
	{
		ldl->head = new;
		ldl->tail = new;
	}
	else
		insert_sort(ldl, new, curr, fcmp);
	ldl->length++;
	return (ldl);
}
