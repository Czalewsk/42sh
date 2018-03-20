/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comp_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bviala <bviala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 00:50:59 by bviala            #+#    #+#             */
/*   Updated: 2018/03/19 18:47:33 by bviala           ###   ########.fr       */
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
	path = ft_strnew(count_tildes(search, len_search, len));
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

t_ldl		*get_current(t_ldl_head *lst)
{
	t_ldl	*ldl;

	ldl = lst ? lst->head : NULL;
	while (ldl)
	{
		if (((t_select *)ldl->content)->is_current)
			return (ldl);
		ldl = ldl->next;
	}
	return (ldl);
}
