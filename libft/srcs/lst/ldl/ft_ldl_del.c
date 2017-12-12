/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:06:40 by bviala            #+#    #+#             */
/*   Updated: 2017/12/08 16:58:27 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ldl_del(t_ldl_head *ldl_head, t_ldl **ldl, void (*del)())
{
	t_ldl	*next;
	t_ldl	*prev;

	DEBUG("ldl\n");
	if (!ldl_head || !ldl || !*ldl)
		return ;
	DEBUG("content is |%s|\n", (*ldl)->content);
	((*ldl)->content && del) ? del(&(*ldl)->content) : NULL;
	DEBUG("content is |%s|\n", (*ldl)->content);
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
	DEBUG("ICI");
	free(*ldl);
	DEBUG("LA");
	ldl_head->length--;
}
