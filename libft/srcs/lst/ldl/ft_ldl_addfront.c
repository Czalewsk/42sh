/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_addfront.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 19:49:13 by bviala            #+#    #+#             */
/*   Updated: 2017/11/09 20:31:31 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ldl_head	*ft_ldl_addfront(t_ldl_head *ldl_head, void *content)
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
			ldl_head->head->prev = new;
			new->next = ldl_head->head;
			ldl_head->head = new;
		}
		ldl_head->length++;
	}
	return (ldl_head);
}
