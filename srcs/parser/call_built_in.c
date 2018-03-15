/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 23:24:26 by maastie           #+#    #+#             */
/*   Updated: 2018/03/15 13:37:45 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

const t_builtin	g_builtins[] = {
	{"export", builtin_export},
	{"unsetenv", builtin_unsetenv},
	{"setenv", builtin_setenv},
	{"cd", builtin_cd},
	{"jobs", bt_jobs},
	{"bg", bt_bg},
	{"fg", bt_fg},
	{"history", builtin_history},
	{"exit", builtin_exit},
	{"echo", builtin_echo},
	{"env", builtin_env},
	{NULL, NULL}
};

int		do_built_in(t_process *p, char **env)
{
	int		i;

	i = -1;
	while (g_builtins[++i].name)
	{
		if (!ft_strcmp(g_builtins[i].name, p->argv[0]))
		{
			g_sh.exitstatus = g_builtins[i].f(p,
					ft_tab2dlen((const void **)p->argv), p->argv, env);
			return (1);
		}
	}
	return (0);
}
