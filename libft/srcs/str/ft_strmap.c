/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:59:50 by bviala            #+#    #+#             */
/*   Updated: 2018/03/16 15:08:44 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strmap(char const *s, char (*f) (char))
{
	size_t		i;
	char		*cpy;

	i = 0;
	if (!s)
		return (NULL);
	cpy = (char*)ft_memalloc(sizeof(char) * (ft_strlen(s) + 1));
	i = 0;
	while (s[i])
	{
		cpy[i] = f(s[i]);
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
