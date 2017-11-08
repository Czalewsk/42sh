/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_pushfront.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:18:10 by bviala            #+#    #+#             */
/*   Updated: 2017/11/08 16:19:14 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ldl_pushfront(t_ldl **ldl, void *content)
{
	t_ldl	*new;
	t_ldl	*front;

	if (!ldl || !*ldl)
		return (ft_ldl_new(ldl, content));
	if ((new = (t_ldl *)malloc(sizeof(t_ldl))))
	{
		front = ft_ldl_front(*ldl);
		new->next = front;
		new->prev = NULL;
		new->content = content;
		front->prev = new;
		*ldl = new;
	}
}
