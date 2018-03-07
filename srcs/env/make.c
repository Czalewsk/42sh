/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 20:09:14 by thugo             #+#    #+#             */
/*   Updated: 2018/03/07 13:20:50 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char		**env_make(char type)
{
	static char	**env;
	static char	curtype;
	size_t		len;
	int			i;

	if (env && !g_sh.envupd && type == curtype)
		return (env);
	curtype = type;
	len = env_len((const t_env **)g_sh.env, type);
	if (env)
		free(env);
	env = (char **)ft_memalloc(sizeof(char *) * (len + 1));
	i = -1;
	len = -1;
	g_sh.envupd = 0;
	while (g_sh.env[++i])
	{
		if (g_sh.env[i]->type & type)
			env[++len] = g_sh.env[i]->var;
		if (type & ENV_TEMP && g_sh.env[i]->type & ENV_TEMP)
			g_sh.env[i]->type = (g_sh.envupd |= 1) >> ENV_DELETE;
		else if (g_sh.env[i]->type & ENV_DELETE)
			env_unsetaddr(g_sh.env + i--);
	}
	return (env);
}
