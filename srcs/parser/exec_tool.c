/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 06:00:51 by maastie           #+#    #+#             */
/*   Updated: 2018/02/25 06:00:52 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char	**extract_string(char *src, char *ref)
{
	char	**ret;
	char	*from;
	int		a;
	int		i;

	i = ft_strlen(src) - ft_strlen(ref);
	if (i <= 0)
		return (NULL);
	from = ft_memalloc(sizeof(char) * i);
	i = 0;
	a = 5;
	while (src && src[a])
		from[i] = src[a++];
	ret = ft_strsplit(from, ':');
	free(from);
	return (ret);
}

char	**extract_from_tab(char **env, char *ref)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_memcmp(env[i], ref, ft_strlen(env[i])) == 0)
			return (extract_string(env[i], ref));
		i++;
	}
	return (ft_strsplit("/Users/maastie/.brew/bin:/Users/maastie/.brew/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/opt/X11/bin:/Applications/VMware", ':'));
}