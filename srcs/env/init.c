/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 20:02:14 by thugo             #+#    #+#             */
/*   Updated: 2018/03/20 15:20:39 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	env_init(const char **env)
{
	int		i;
	char	*shlvl;
	int		level;

	g_sh.env = (t_env **)ft_memalloc(sizeof(t_env *) *
			((size_t)ft_tab2dlen((const void **)env) + 1));
	i = -1;
	while (env[++i])
	{
		g_sh.env[i] = (t_env *)ft_memalloc(sizeof(t_env));
		g_sh.env[i]->var = ft_strdup(env[i]);
		g_sh.env[i]->type = ENV_GLOBAL;
	}
	if ((shlvl = ft_getenv((char **)env, "SHLVL")) && ft_isint(shlvl))
		level = ft_atoi(shlvl);
	else
		level = 0;
	shlvl = ft_itoa(level + 1);
	env_set("SHLVL", shlvl, ENV_GLOBAL);
	g_sh.envupd = 1;
	free(shlvl);
}
