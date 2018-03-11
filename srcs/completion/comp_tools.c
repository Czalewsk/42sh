/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 00:50:59 by bviala            #+#    #+#             */
/*   Updated: 2018/03/09 01:56:05 by bviala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	count_tildes(char *search, size_t len, int len_home)
{
	char	*tmp;

	tmp = search;
	while (tmp && (tmp = ft_strchr(tmp, '~')))
	{
		if (!(tmp + 1) || ((tmp + 1) && *(tmp + 1) != '~'))
			len = len + len_home - 1;
		tmp++;
	}
	return (len);
}

char		*comp_checktilde(char *search, size_t len_search, char *home)
{
	char	*path;
	char	*tmp;
	int		len;
	int		i;

	len = ft_strlen(home);
	if (!search)
		return (ft_strdup("./\0"));
	path = ft_memalloc(count_tildes(search, len_search, len));
	tmp = search;
	i = 0;
	while (tmp && *tmp)
	{
		if (*tmp == '~' && ((tmp + 1) || ((tmp + 1) && *(tmp + 1) != '~')))
		{
			path = ft_strcat(path, home);
			i += len;
			tmp++;
		}
		path[i] = *tmp++;
		++i;
	}
	path[i] = '\0';
	return (path);
}
