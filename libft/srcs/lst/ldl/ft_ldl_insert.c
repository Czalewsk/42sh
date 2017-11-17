/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 21:51:10 by bviala            #+#    #+#             */
/*   Updated: 2017/11/14 18:01:09 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ldl_head	*ft_ldl_insert(t_ldl_head *ldl, void *content, size_t pos)
{
	size_t	i;
	t_ldl	*new;
	t_ldl	*curr;

	new = NULL;
	if ((i = 0) || !ldl || pos > ldl->length + 1)
		return (ldl);
	if (((curr = ldl->head) && pos == ldl->length + 1) || !curr)
		return (ft_ldl_addback(ldl, content));
	while (curr && ++i != pos)
		curr = curr->next;
	if (curr && i == pos)
	{
		if (!curr->prev)
			return (ft_ldl_addfront(ldl, content));
		ft_ldl_new_node(&new, content);
		curr->prev->next = new;
		new->prev = curr->prev;
		new->next = curr;
		ldl->length++;
		curr->prev = new;
		if (curr->next)
			curr->next->prev = curr;
	}
	return (ldl);
}
