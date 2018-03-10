/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:26:09 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/10 13:58:37 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	launch_process(char *tmp, t_process *p, t_job *j, char **env)
{
	pid_t	pid;
	pid_t	pgid;

	if (shell_is_interactive)
	{
		pid = getpid();
		if (j && j->pgid == 0)
			j->pgid = pid;
		else
			pgid = pid;
		setpgid(pid, j ? j->pgid : pgid);
		if (!j && tcsetpgrp(shell_terminal, pgid) == -1)
			exit(sh_error(1, 0, NULL, 1, "Erreur tcsetpgrp launch_process\n"));
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
	}
	exit(g_sh.exitstatus = execve(tmp, p->argv, env));
}
