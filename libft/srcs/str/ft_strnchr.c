/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:52:21 by bviala            #+#    #+#             */
/*   Updated: 2017/12/11 10:40:15 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *str, int c, size_t len)
{
	if ((char)c == '\0')
	{
		while (*str != (char)c && *str && len--)
			str++;
		return ((char*)str);
	}
	while (*str != (char)c && *str && len--)
		str++;
	return ((*str == '\0' || !len) ? NULL : (char*)str);
}
