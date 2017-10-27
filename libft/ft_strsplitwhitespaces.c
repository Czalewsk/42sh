/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplitwhitespaces.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 16:37:59 by czalewsk          #+#    #+#             */
/*   Updated: 2017/10/18 16:54:35 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_count_world(char const *s)
{
	size_t	n;
	size_t	i;

	i = 0;
	n = 1;
	while (s[i])
	{
		if (i == 0 && s[i] != 32 && s[i] != 10 && s[i] != 9)
			n++;
		else if (i != 0 && s[i] != 32 && s[i] != 10 && s[i] != 9
				&& (s[i - 1] == 32 || s[i - 1] == 9 || s[i - 1] == 10))
			n++;
		i++;
	}
	return (n);
}

static	char	*ft_split_word(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != 32 && s[i] != 10 && s[i] != 9)
		i++;
	return (ft_strsub(s, 0, i));
}

char			**ft_strsplitwhitespaces(char const *s)
{
	char	**split;
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (!s)
		return (NULL);
	split = (char**)ft_memalloc(ft_count_world(s) * (sizeof(char**)));
	while (s[i])
	{
		if (i == 0 && s[i] != 32 && s[i] != 10 && s[i] != 9)
			split[n++] = ft_split_word(&(s[i]));
		else if (i != 0 && s[i] != 32 && s[i] != 10 && s[i] != 9
				&& (s[i - 1] == 32 || s[i - 1] == 9 || s[i - 1] == 10))
			split[n++] = ft_split_word(&(s[i]));
		i++;
	}
	split[n] = NULL;
	return (split);
}
