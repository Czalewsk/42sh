/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 14:49:03 by bviala            #+#    #+#             */
/*   Updated: 2017/08/11 14:55:09 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstswap(t_list *list)
{
	t_list	*new;

	new = list;
	if (list && list->next)
	{
		new = list->next;
		list->next = new->next;
		new->next = list;
	}
	return (new);
}
