/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 16:36:55 by czalewsk          #+#    #+#             */
/*   Updated: 2017/10/18 10:37:22 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_split_word(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (ft_strsub(s, 0, i));
}

t_list			*ft_strsplit_lst(char const *s, char c)
{
	t_list		*start;
	size_t		i;
	char		*tmp;

	i = 0;
	if (!s || !c)
		return (NULL);
	start = NULL;
	while (s[i])
	{
		if (i == 0 && s[i] != c && (tmp = ft_split_word((s + i), c)))
			ft_lst_pushend(&start, ft_lstnew(tmp, ft_strlen(tmp) + 1));
		else if (i != 0 && s[i] != c && s[i - 1] == c
				&& (tmp = ft_split_word((s + i), c)))
			ft_lst_pushend(&start, ft_lstnew(tmp, ft_strlen(tmp) + 1));
		i++;
		ft_strdel(&tmp);
	}
	return (start);
}
