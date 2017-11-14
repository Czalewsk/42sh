/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_new_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:58:11 by bviala            #+#    #+#             */
/*   Updated: 2017/11/14 14:32:57 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ldl_new_node(t_ldl **ldl, void *content)
{
	t_ldl	*new;

	if ((new = (t_ldl *)malloc(sizeof(t_ldl))))
	{
		new->content = content;
		new->prev = NULL;
		new->next = NULL;
		*ldl = new;
	}
}
