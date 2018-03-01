/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:48:41 by thugo             #+#    #+#             */
/*   Updated: 2018/03/01 23:57:30 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_env	**env_getaddr(const char *name)
{
	int		i;
	size_t	len1;
	size_t	len2;

	i = -1;
	len1 = ft_strlen(name);
	while (g_sh.env[++i])
	{
		if (g_sh.env[i]->type & (ENV_LOCAL | ENV_GLOBAL))
		{
			len2 = ft_strchr(g_sh.env[i]->var, '=') - g_sh.env[i]->var;
			if (len1 == len2 && !ft_strncmp(name, g_sh.env[i]->var, len1))
				return (g_sh.env + i);
		}
	}
	return (NULL);
}

char	*env_get(const char *name)
{
	int		i;
	size_t	len1;
	size_t	len2;

	i = -1;
	len1 = ft_strlen(name);
	while (g_sh.env[++i])
	{
		if (g_sh.env[i]->type & (ENV_LOCAL | ENV_GLOBAL))
		{
			len2 = ft_strchr(g_sh.env[i]->var, '=') - g_sh.env[i]->var;
			if (len1 == len2 && !ft_strncmp(name, g_sh.env[i]->var, len1))
				return (g_sh.env[i]->var + len1 + 1);
		}
	}
	return (NULL);
}
