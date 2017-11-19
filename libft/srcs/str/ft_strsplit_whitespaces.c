/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_whitespaces.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 20:11:26 by bviala            #+#    #+#             */
/*   Updated: 2017/09/06 20:50:36 by bviala           ###   ########.fr       */
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
	if (!(tab = (char **)malloc(sizeof(*tab) * (ft_countwords(str) + 1))))
		return (NULL);
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
