/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_new_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:58:11 by bviala            #+#    #+#             */
/*   Updated: 2017/12/06 12:05:36 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ldl_new_node(t_ldl **ldl, void *content)
{
	t_ldl	*new;

	new = (t_ldl *)ft_memalloc(sizeof(t_ldl));
	new->content = content;
	*ldl = new;
}
