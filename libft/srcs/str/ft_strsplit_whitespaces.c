/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_whitespaces.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 20:11:26 by bviala            #+#    #+#             */
/*   Updated: 2018/03/16 15:09:46 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(const char *str)
{
	int		len;

	len = 0;
	while (*str)
	{
		while (*str && ft_isspace(*str))
			++str;
		if (*str)
			len++;
		while (*str && !ft_isspace(*str))
			++str;
	}
	return (len);
}

char		**ft_strsplit_whitespaces(const char *str)
{
	char	**tab;
	int		i;
	int		len;

	if (!str)
		return (NULL);
	tab = (char **)ft_memalloc(sizeof(*tab) * (ft_countwords(str) + 1));
	i = 0;
	while (*str && ft_isspace(*str))
		++str;
	while (*str)
	{
		len = 0;
		while (str[len] && !ft_isspace(str[len]))
			len++;
		tab[i] = ft_strndup(str, len);
		i++;
		str = str + len;
		while (*str && ft_isspace(*str))
			++str;
	}
	tab[i] = 0;
	return (tab);
}
