/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_addback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:16:44 by bviala            #+#    #+#             */
/*   Updated: 2017/11/09 20:48:35 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ldl_head	*ft_ldl_addback(t_ldl_head *ldl_head, void *content)
{
	t_ldl		*new;

	if (!ldl_head)
		return (NULL);
	ft_ldl_new_node(&new, content);
	if (new)
	{
		if (!ldl_head->tail)
		{
			ldl_head->head = new;
			ldl_head->tail = new;
		}
		else
		{
			ldl_head->tail->next = new;
			new->prev = ldl_head->tail;
			ldl_head->tail = new;
		}
		ldl_head->length++;
	}
	return (ldl_head);
}
