/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:56:54 by bviala            #+#    #+#             */
/*   Updated: 2017/08/23 16:47:02 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *str, const char *to_find)
{
	size_t	len;
	size_t	len_new;

	if (!*to_find)
		return ((char*)str);
	len = ft_strlen(to_find);
	len_new = ft_strlen(str);
	while (*str && len <= len_new)
	{
		if (!ft_strncmp(str, to_find, len))
			return ((char *)str);
		str++;
		len_new--;
	}
	return (NULL);
}
