/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 20:09:14 by thugo             #+#    #+#             */
/*   Updated: 2018/03/02 00:17:25 by thugo            ###   ########.fr       */
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
		ft_printf("-- Var: %s | Type: %i\n", g_sh.env[i]->var, g_sh.env[i]->type);
		if (g_sh.env[i]->type & type)
			env[++len] = g_sh.env[i]->var;
		if (type & ENV_TEMP && g_sh.env[i]->type & ENV_TEMP){
			ft_printf("Set delete: %s\n", g_sh.env[i]->var);
			g_sh.envupd = 1;
			g_sh.env[i]->type = ENV_DELETE;
		}else if (g_sh.env[i]->type & ENV_DELETE){
			ft_printf("Delete: %s\n", g_sh.env[i]->var);
			env_unsetaddr(g_sh.env + i--);}
	}
	ft_printf("-- ENV UPDATE: %i\n", g_sh.envupd);
	return (env);
}
