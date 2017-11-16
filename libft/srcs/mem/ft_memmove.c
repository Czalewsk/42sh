/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:45:59 by bviala            #+#    #+#             */
/*   Updated: 2017/07/18 14:46:01 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest2;
	unsigned char	*src2;

	dest2 = (unsigned char*)dest;
	src2 = (unsigned char*)src;
	if (src2 < dest2)
	{
		dest2 += n;
		src2 += n;
		while (n--)
			*--dest2 = *--src2;
	}
	else
	{
		while (n--)
			*dest2++ = *src2++;
	}
	return (dest);
}
