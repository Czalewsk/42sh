/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 13:53:40 by bviala            #+#    #+#             */
/*   Updated: 2018/03/16 15:08:32 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char const *s1, char const *s2, int i)
{
	char	*str;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)ft_memalloc(sizeof(char) * (len + 1));
	str = ft_strcpy(str, s1);
	str = ft_strcat(str, s2);
	if (i == 0)
		free((char *)s1);
	if (i == 1)
		free((char *)s2);
	if (i == 2)
	{
		free((char *)s1);
		free((char *)s2);
	}
	return (str);
}
