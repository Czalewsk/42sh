/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:56:19 by bviala            #+#    #+#             */
/*   Updated: 2017/07/18 14:56:21 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *str, int n)
{
	char	*save;

	save = 0;
	if ((unsigned char)n == '\0')
	{
		while (*str)
			str++;
		save = (char*)(str++);
		return (save);
	}
	while (*str)
	{
		if (*str == (char)n)
			save = (char*)str;
		str++;
	}
	return ((save != 0) ? save : NULL);
}
