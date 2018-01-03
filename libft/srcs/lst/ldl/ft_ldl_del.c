/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:06:40 by bviala            #+#    #+#             */
/*   Updated: 2017/12/28 19:38:55 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ldl_del(t_ldl_head *ldl_head, t_ldl **ldl, void (*del)())
{
	t_ldl	*next;
	t_ldl	*prev;

	if (!ldl_head || !ldl || !*ldl)
		return ;
	((*ldl)->content && del) ? del(&(*ldl)->content) : NULL;
	prev = (*ldl)->prev;
	next = (*ldl)->next;
	if (!next && prev)
	{
		ldl_head->tail = prev;
		prev->next = NULL;
	}
	else if (!prev && next)
	{
		ldl_head->head = next;
		next->prev = NULL;
	}
	else if (next && prev)
	{
		next->prev = prev;
		prev->next = next;
	}
	free(*ldl);
	ldl_head->length--;
}
