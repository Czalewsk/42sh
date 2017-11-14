/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_new_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:03:10 by bviala            #+#    #+#             */
/*   Updated: 2017/11/09 18:36:03 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ldl_head	*ft_ldl_new_list(void)
{
	t_ldl_head	*new;

	if ((new = (t_ldl_head *)malloc(sizeof(t_ldl_head))))
	{
		new->length = 0;
		new->head = NULL;
		new->tail = NULL;
	}
	return (new);
}
