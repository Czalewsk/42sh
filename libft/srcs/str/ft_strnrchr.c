/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnrchr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 16:47:27 by thugo             #+#    #+#             */
/*   Updated: 2018/03/27 16:48:58 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnrchr(const char *s, char c, size_t size)
{
	char	*save;
	int		i;

	save = NULL;
	if (c == '\0')
		return ((char *)s + ft_strlen(s));
	i = -1;
	while (s[++i] && i < (int)size)
		if (s[i] == c)
			save = (char *)s + i;
	return (save);
}
