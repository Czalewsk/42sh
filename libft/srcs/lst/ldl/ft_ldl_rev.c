/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_rev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:41:23 by bviala            #+#    #+#             */
/*   Updated: 2017/11/14 16:54:31 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ldl_head	*ft_ldl_rev(t_ldl_head *ldl)
{
	t_ldl_head	*new;
	t_ldl		*temp;

	if (!ldl || !(new = ft_ldl_new_list()))
		return (NULL);
	temp = ldl->tail;
	while (temp)
	{
		new = ft_ldl_addback(new, temp->content);
		temp = temp->prev;
	}
	free(ldl);
	return (new);
}
