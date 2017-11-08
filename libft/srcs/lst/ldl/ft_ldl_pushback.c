/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_pushback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:16:06 by bviala            #+#    #+#             */
/*   Updated: 2017/11/08 18:26:50 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ldl_pushback(t_ldl **ldl, void *content)
{
	t_ldl	*new;
	t_ldl	*back;

	if (!ldl || !*ldl)
		return (ft_ldl_new(ldl, content));
	if ((new = (t_ldl *)malloc(sizeof(t_ldl))))
	{
		back = ft_ldl_back(*ldl);
		new->prev = back;
		new->next = NULL;
		new->content = content;
		back->next = new;
	}
}
