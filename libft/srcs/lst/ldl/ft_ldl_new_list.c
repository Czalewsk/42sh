/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldl_new_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:03:10 by bviala            #+#    #+#             */
/*   Updated: 2017/12/06 15:00:11 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

extern inline t_ldl_head	*ft_ldl_new_list(void)
{
	return ((t_ldl_head *)ft_memalloc(sizeof(t_ldl_head)));
}
