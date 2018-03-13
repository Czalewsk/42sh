/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:54:12 by maastie           #+#    #+#             */
/*   Updated: 2018/03/04 13:59:42 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int				exec_with_acces(char *tmp, t_process *p, t_job *job, char **env)
{
	pid_t		father;
	int			i;

	termcaps_restore_tty();
	if ((father = fork()) == -1)
		exit(-1);
	i = 0;
	if (father == 0)
	{
		if (job)
			setpgid(getpid(), getpid());// je suis pas sur que ca reste
		exit(execve(tmp, p->argv, env));
	}
	else
	{
		if (!job)
			while (waitpid(father, &g_sh.exitstatus, 0) == -1
					&& errno == EINTR)
					;
		else
		{
			dprintf(g_sh.fd_tty, "[%d] %d\n", job->num, father);
			p->pid = father;
			g_sh.exitstatus = 0;
			job->pgid = p->pid;
			DEBUG("\n\nPROCESS : %d --- %d --- %d --- %d --- %d --- %d --- %d\n", p->pid, p->completed, p->stopped, p->status, p->stdin, p->stdout, p->stderr);
			job->process = ft_memalloc(sizeof(t_process));
			ft_memcpy(job->process, p, sizeof(t_process));
			job->process->argv = ft_memdup(p->argv, sizeof(char*) * (ft_tab2dlen((const void**)(p->argv)) + 1));
			while(p->argv[i])
			{
				job->process->argv[i] = ft_memdup(p->argv[i], sizeof(char) * (ft_strlen(p->argv[i]) + 1));
				i++;
			}
			DEBUG("JOB->PROCESS : %d --- %d --- %d --- %d --- %d --- %d --- %d\n", job->process->pid, job->process->completed, job->process->stopped, job->process->status, job->process->stdin, job->process->stdout, job->process->stderr);
		}
	}
	p->returned = g_sh.exitstatus;
	termcaps_set_tty();
	return (g_sh.exitstatus);
}

int				exec_with_acces_no_fork(char *tmp, t_process *p, t_job *job, char **env)
{
	(void)job;
	exit(execve(tmp, p->argv, env));
}

int				exec_in_line(t_process *p, t_job *job, char **env)
{
	if (access(p->argv[0], X_OK | F_OK) != -1)
	{
		exec_with_acces(p->argv[0], p, job, env);
		return (0);
	}
	return (1);
}

int				execute(t_process *p, t_job *job, char **env, int k)
{
	char		**path;
	char		*exec_line;
	int			i;

	i = 0;
	if (ft_strstr(p->argv[0], "/") != NULL)
		if (exec_in_line(p, job, env) == 0)
			return (-1);
	path = ft_strsplit(ft_getenv(env, "PATH"), ':');
	while (path && path[i])
	{
		exec_line = ft_strjoin(path[i++], "/");
		exec_line = ft_strjoin_free(exec_line, p->argv[0], 0);
		if (access(exec_line, X_OK | F_OK) != -1)
		{
			if (k == 0)
				exec_with_acces_no_fork(exec_line, p, job, env);
			else
				exec_with_acces(exec_line, p, job, env);
			ft_strdel(&exec_line);
			return (clear_execute(path, p));// pas de free sur process;
		}
		ft_strdel(&exec_line);
	}
	sh_error(0, 0, NULL, 3, "command not found: ", p->argv[0], "\n");
	p->returned = -1;
	return (clear_execute(path, p));// pas de free sur process;
}