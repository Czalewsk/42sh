/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:42:59 by maastie           #+#    #+#             */
/*   Updated: 2018/03/27 11:48:53 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			clear_execute(char **path, t_process *p)
{
	(void)p;
	ft_free_array(path);
	return (g_sh.exitstatus);
}

void		pere(t_job *j, t_process *pr, int p[2][2], char **env)
{
	if (pr->pid && !j->pgid)
	{
		j->pgid = pr->pid;
		setpgid(pr->pid, j->pgid);
		if (j->foreground == 1 && tcsetpgrp(g_shell_terminal, j->pgid) == -1)
			exit(sh_error(1, 0, NULL, 1, "Erreur tcsetpgrp launch_process\n"));
	}
	setpgid(pr->pid, j->pgid);
	if (!pr->pid)
		executor(j, pr, p, env);
	if (pr != j->process)
		close(p[1][0]);
	p[1][0] = p[0][0];
}

void		just_the_last(t_process *p)
{
	p->stderr = 2;
	p->stdout = 1;
	p->stdin = 0;
}
