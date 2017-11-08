/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_reverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:19:47 by bviala            #+#    #+#             */
/*   Updated: 2017/11/08 16:43:11 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ldl_reverse(t_ldl **ldl)
{
	t_ldl	*l_prev;
	t_ldl	*l_next;
	t_ldl	*l_cur;

	l_cur = ft_ldl_front(*ldl);
	l_prev = NULL;
	while (l_cur)
	{
		l_next = l_cur->next;
		l_cur->next = l_prev;
		l_cur->prev = l_next;
		l_prev = l_cur;
		l_cur = l_next;
	}
	*ldl = l_prev;
}
