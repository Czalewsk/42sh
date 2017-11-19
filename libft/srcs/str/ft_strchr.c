/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:52:21 by bviala            #+#    #+#             */
/*   Updated: 2017/07/18 14:52:23 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	if ((char)c == '\0')
	{
		while (*str != (char)c && *str)
			str++;
		return ((char*)str);
	}
	while (*str != (char)c && *str)
		str++;
	return (*str == '\0' ? NULL : (char*)str);
}
