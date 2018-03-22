/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czalewsk <czalewsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 19:24:49 by czalewsk          #+#    #+#             */
/*   Updated: 2018/03/22 16:01:50 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static int	g_displayed;

int			builtin_exit(t_process *p, int argc, char **argv, char **env)
{
	(void)p;
	(void)env;
	if (argc > 2)
		return (sh_error(1, 1, NULL, 1, "exit: too many arguments\n"));
	if (!g_displayed && g_first_job)
	{
		g_displayed++;
		return (sh_error(1, 1, NULL, 1, "exit\nThere are stopped jobs.\n"));
	}
	g_sh_exit = 1;
	return (argc == 2 ? ft_atoi(argv[1]) : g_sh.exitstatus);
}

char		sh_quit_ctrld(t_buf *cmd, t_read *info, t_key *entry)
{
	(void)info;
	(void)entry;
	if (!cmd->size_actual && !g_sh.prompt_add)
	{
		if (!g_displayed && g_first_job)
		{
			g_displayed++;
			g_new_prompt = 1;
			ft_bzero(entry, sizeof(t_key));
			return (sh_error(-2, 1, NULL, 1,
						"exit\nThere are stopped jobs."));
		}
		g_sh_exit = 1;
		write(g_sh.fd_tty, "exit\n", 5);
		return (-3);
	}
	ft_bzero(entry, sizeof(t_key));
	return (1);
}
