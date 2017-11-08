/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:43:18 by bviala            #+#    #+#             */
/*   Updated: 2017/11/08 16:44:48 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_ldl_size(t_ldl *ldl)
{
	size_t	size;

	size = 0;
	ldl = ft_ldl_front(ldl);
	while (ldl)
	{
		ldl = ldl->next;
		size++;
	}
	return (size);
}
