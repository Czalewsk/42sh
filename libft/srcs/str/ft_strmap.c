/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 14:59:50 by bviala            #+#    #+#             */
/*   Updated: 2017/07/18 14:59:52 by bviala           ###   ########.fr       */
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
	if (!(cpy = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	i = 0;
	while (s[i])
	{
		cpy[i] = f(s[i]);
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
