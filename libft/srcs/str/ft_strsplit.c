/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 14:47:00 by bviala            #+#    #+#             */
/*   Updated: 2018/03/16 15:09:31 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(const char *str, char c)
{
	int		len;

	len = 0;
	while (*str)
	{
		while (*str && *str == c)
			++str;
		if (*str)
			len++;
		while (*str && *str != c)
			++str;
	}
	return (len);
}

char		**ft_strsplit(const char *str, char c)
{
	char	**tab;
	int		i;
	int		len;

	if (!str)
		return (NULL);
	tab = (char **)ft_memalloc(sizeof(*tab) * (ft_countwords(str, c) + 1));
	i = 0;
	while (*str && *str == c)
		++str;
	while (*str)
	{
		len = 0;
		while (str[len] && str[len] != c)
			len++;
		tab[i] = ft_strndup(str, len);
		i++;
		str = str + len;
		while (*str && *str == c)
			++str;
	}
	tab[i] = 0;
	return (tab);
}
