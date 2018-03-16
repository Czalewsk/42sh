/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:53:06 by bviala            #+#    #+#             */
/*   Updated: 2018/03/16 15:08:10 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *src)
{
	char	*dest;

	if (!src)
		return (NULL);
	dest = (char*)ft_memalloc((ft_strlen(src) + 1) * sizeof(char));
	ft_strcpy(dest, src);
	return (dest);
}
