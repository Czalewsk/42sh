/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:53:55 by bviala            #+#    #+#             */
/*   Updated: 2017/07/18 14:53:57 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		d;
	int		i;
	char	*cpy;

	d = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(cpy = (char*)malloc(sizeof(char) *
					((ft_strlen((char*)s1) + ft_strlen((char*)s2) + 1)))))
		return (NULL);
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	while (s2[d])
	{
		cpy[i] = s2[d];
		d++;
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
