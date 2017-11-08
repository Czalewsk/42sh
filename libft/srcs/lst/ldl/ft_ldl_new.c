/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:13:37 by bviala            #+#    #+#             */
/*   Updated: 2017/11/08 18:25:56 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ldl_new(t_ldl **ldl, void *content)
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
