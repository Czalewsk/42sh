/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:06:40 by bviala            #+#    #+#             */
/*   Updated: 2017/11/08 18:58:23 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ldl_del(t_ldl **ldl, void (*del)())
{
	t_ldl	*next;
	t_ldl	*prev;

	if (!ldl || !*ldl)
		return ;
	if ((*ldl)->content && del)
		del(&(*ldl)->content);
	next = (*ldl)->next;
	prev = (*ldl)->prev;
	free(*ldl);
	if (prev)
	{
		prev->next = next;
		*ldl = prev;
	}
	else
		*ldl = next;
	if (next)
		*ldl = next;
}
