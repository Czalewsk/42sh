/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:54:07 by bviala            #+#    #+#             */
/*   Updated: 2017/07/18 14:54:08 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		size2;
	size_t		len;
	char		*dest2;
	const char	*src2;

	dest2 = dest;
	src2 = src;
	size2 = size;
	while (size2-- != 0 && *dest2 != '\0')
		dest2++;
	len = dest2 - dest;
	size2 = size - len;
	if (size2 == 0)
		return (len + ft_strlen(src2));
	while (*src2 != '\0')
	{
		if (size2 != 1)
		{
			*dest2++ = *src2;
			size2--;
		}
		src2++;
	}
	*dest2 = '\0';
	return (len + (src2 - src));
}
