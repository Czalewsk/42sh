/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:53:06 by bviala            #+#    #+#             */
/*   Updated: 2017/09/06 15:19:00 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *src, size_t len)
{
	char	*dest;

	if (!(dest = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	dest[len] = '\0';
	dest = ft_memcpy(dest, src, len);
	return (dest);
}
