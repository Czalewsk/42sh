/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:54:12 by maastie           #+#    #+#             */
/*   Updated: 2018/03/13 17:34:34 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int				exec_with_acces(char *tmp, t_process *p, t_job *job, char **env)
{
	pid_t		pid;
	
	termcaps_restore_tty();
	if ((pid = fork()) == -1)
		exit(sh_error(-1, 0, NULL, 1, "Erreur fork exec_with_acces\n"));
	if (pid == 0)
		launch_process(tmp, p, job, env);
	p->pid = pid;
	if (g_shell_is_interactive)
	{
		if (job && !job->pgid)
			job->pgid = pid;
		setpgid (pid, pid);
	}
	if (job->foreground == 0)
		put_process_in_foreground(p, 1);
	else
	{
		dprintf(g_sh.fd_tty, "[%d] %d\n", job->num, pid);
		g_sh.exitstatus = 0;
		job->process = cpy_profonde_process(p);
		job->process->status = g_sh.exitstatus;
	}
	termcaps_set_tty();
	return (g_sh.exitstatus);
}

int				exec_with_acces_no_fork(char *tmp, t_job *job, char **env)
{
	exit(execve(tmp, job->process->argv, env));
}

int				exec_in_line(t_job *job, char **env)
{
	if (access(job->process->argv[0], X_OK | F_OK) != -1)
	{
		exec_with_acces(job->process->argv[0], job->process, job, env);
		return (0);
	}
	return (1);
}

int				execute(t_job *job, char **env, int k)
{
	char		**path;
	char		*exec_line;
	int			i;

	i = 0;
	if (ft_strstr(job->process->argv[0], "/") != NULL)
		if (exec_in_line(job, env) == 0)
			return (-1);
	path = ft_strsplit(ft_getenv(env, "PATH"), ':');
	while (path && path[i])
	{
		exec_line = ft_strjoin(path[i++], "/");
		exec_line = ft_strjoin_free(exec_line, job->process->argv[0], 0);
		if (access(exec_line, X_OK | F_OK) != -1)
		{
			if (k == 0)
				exec_with_acces_no_fork(exec_line, job, env);
			else
				exec_with_acces(exec_line, job->process, job, env);
			ft_strdel(&exec_line);
			return (clear_execute(path, job->process));// pas de free sur process;
		}
		ft_strdel(&exec_line);
	}
	sh_error(0, 0, NULL, 3, "command not found: ", job->process->argv[0], "\n");
	job->process->status = -1;
	return (clear_execute(path, job->process));// pas de free sur process;
}
