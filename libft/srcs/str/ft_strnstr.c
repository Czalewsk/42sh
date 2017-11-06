/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:56:04 by bviala            #+#    #+#             */
/*   Updated: 2017/08/23 16:46:38 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	len;
	size_t	len_new;

	if (!*to_find)
		return ((char*)str);
	len = ft_strlen(to_find);
	len_new = ft_strlen(str);
	while (*str && n >= len && len <= len_new)
	{
		if (!ft_strncmp(str, to_find, len))
			return ((char*)str);
		n--;
		len_new--;
		str++;
	}
	return (NULL);
}
