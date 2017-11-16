/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:44:59 by bviala            #+#    #+#             */
/*   Updated: 2017/07/18 14:45:01 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buffer, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char*)buffer == (unsigned char)c)
			return ((void*)buffer);
		buffer++;
	}
	return (NULL);
}
