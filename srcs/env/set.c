/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <thugo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 17:43:57 by thugo             #+#    #+#             */
/*   Updated: 2018/03/08 19:26:59 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	env_add(const char *name, const char *value, char type)
{
	t_env	**new;
	int		len;

	len = env_len((const t_env **)g_sh.env, ENV_LOCAL | ENV_GLOBAL | ENV_TEMP);
	new = ft_memalloc(sizeof(t_env *) * (len + 2));
	ft_memcpy((void *)new, (void *)g_sh.env, len * sizeof(t_env *));
	new[len] = (t_env *)ft_memalloc(sizeof(t_env));
	if (type & ENV_TEMP)
		new[len]->temp = ft_strxjoin(3, name, "=", value);
	else
		new[len]->var = ft_strxjoin(3, name, "=", value);
	new[len]->type = type;
	free(g_sh.env);
	g_sh.env = new;
}

void		env_set(const char *name, const char *value, char type)
{
	t_env	**found;

	if ((found = env_getaddr(name, ENV_LOCAL | ENV_GLOBAL | ENV_TEMP)))
	{
		if (type & ENV_TEMP)
		{
			(*found)->temp = ft_strxjoin(3, name, "=", value);
			(*found)->type = ((*found)->type & ~ENV_DELETE) | ENV_TEMP;
		}
		else
		{
			free((*found)->var);
			(*found)->var = ft_strxjoin(3, name, "=", value);
		}
	}
	else
		env_add(name, value, type);
	g_sh.envupd = 1;
}

void		env_settype(const char *name, char type)
{
	t_env	**found;

	if ((found = env_getaddr(name, ENV_LOCAL | ENV_GLOBAL | ENV_TEMP)))
	{
		(*found)->type = type;
		g_sh.envupd = 1;
	}
}
