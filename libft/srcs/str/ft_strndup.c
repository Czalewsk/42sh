/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:53:06 by bviala            #+#    #+#             */
/*   Updated: 2018/03/16 15:09:05 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *src, size_t len)
{
	char	*dest;

	dest = (char*)ft_memalloc((len + 1) * sizeof(char));
	dest[len] = '\0';
	dest = ft_memcpy(dest, src, len);
	return (dest);
}
