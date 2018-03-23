/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 23:24:26 by maastie           #+#    #+#             */
/*   Updated: 2018/03/18 20:11:43 by czalewsk         ###   ########.fr       */
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

void	set_fd(t_process *p)
{
	if (p->stdin != STDIN_FILENO)
		dup2(p->stdin, STDIN_FILENO);
	if (p->stdin != STDOUT_FILENO)
		dup2(p->stdout, STDOUT_FILENO);
	if (p->stdin != STDERR_FILENO)
		dup2(p->stderr, STDERR_FILENO);
}

void	reset_fd(t_process *p)
{
	if (p->stdin != STDIN_FILENO)
		dup2(g_sh.fds[0], STDIN_FILENO);
	if (p->stdin != STDOUT_FILENO)
		dup2(g_sh.fds[1], STDOUT_FILENO);
	if (p->stdin != STDERR_FILENO)
		dup2(g_sh.fds[2], STDERR_FILENO);
}

int		do_built_in(t_process *p, char **env)
{
	int		i;

	i = -1;
	if (!p->argv)
		return (0);
	while (g_builtins[++i].name)
	{
		if (!ft_strcmp(g_builtins[i].name, p->argv[0]))
		{
			set_fd(p);
			g_sh.exitstatus = g_builtins[i].f(p,
					ft_tab2dlen((const void **)p->argv), p->argv, env);
			reset_fd(p);
			return (1);
		}
	}
	return (0);
}
