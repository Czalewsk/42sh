/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:56:12 by bviala            #+#    #+#             */
/*   Updated: 2017/11/08 16:05:21 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_ldl_clear(t_ldl **ldl, void (*del)())
{
	if (!ldl || !*ldl)
		return ;
	*ldl = ft_ldl_front(*ldl);
	while (*ldl)
		ft_ldl_del(ldl, del);
}
