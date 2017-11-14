/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_insert_sort.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 19:08:54 by bviala            #+#    #+#             */
/*   Updated: 2017/11/14 19:52:26 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ldl_head	*ft_ldl_insert_sort(t_ldl_head *ldl, t_ldl *new, int (*fcmp)())
{
	t_ldl	*curr;

	if (!ldl || !new)
		return (ldl);
	if (!(curr = ldl->head))
	{

		ldl->head = new;
		ldl->tail = new;
		ldl->length++;
	}
	else
	{
		while (curr && fcmp(curr->content, new->content) > 0)
			curr = curr->next;
		if (curr)
		{
			if (!curr->prev)
			{
				ldl->head = new;
				new->next = curr;
				curr->prev = new;
				ldl->length++;
				return (ldl);
			}
	//		curr->prev->next = new;
	//		new->prev = curr->prev;
	//		new->next = curr;
	//		ldl->length++;
	//		curr->prev = new;
	//		if (curr->next)
	//			curr->next->prev = curr;
		}
	}
	return (ldl);
}
