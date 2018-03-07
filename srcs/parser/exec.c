/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:54:12 by maastie           #+#    #+#             */
/*   Updated: 2018/03/07 19:28:07 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern	t_fill_job	g_fill_jobs[];

t_process		*fill_for_exec(t_tree *c, t_tree *stop)
{
	int			i;
	t_process	*p;

	i = 0;
	p = NULL;
	p = init_process(p);
	while (c && g_fill_jobs[i].fjob && c != stop)
	{
		if (c && g_fill_jobs[i].one == c->token.id)
		{
			c = g_fill_jobs[i].fjob(p, c);
			if (c == (void *)1)
			{
				ft_free_process(p);
				return ((void *)1);
			}
			i = -1;
		}
		i++;
	}
	return (p);
}

int				exec_with_acces(char *tmp, t_process *p, t_job *job, char **env)
{
	pid_t		father;
	int			i;

	
	termcaps_restore_tty();
	// if (job)
	// {
	// 	DEBUG("tst");
	// 	ft_putendl_fd("", STDOUT_FILENO);
	// }
	if ((father = fork()) == -1)
		exit(-1);
	// if (job)
	// {
	// 	p->pid = getpid();
	// 	job->pgid = setpgid(getpid(), getpid());
	// }
	i = 0;
	if (father == 0)
	{
		signal (SIGTSTP, SIG_IGN);
		if (job)
			setpgid(getpid(), getpid());
		exit(g_sh.exitstatus = execve(tmp, p->argv, env));
	}
	else
	{
		if (!job)
			waitpid(father, &g_sh.exitstatus, WUNTRACED | WCONTINUED);
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
	termcaps_set_tty();
	return (g_sh.exitstatus);
}

static int		exec_in_line(t_process *p, t_job *job, char **env)
{
	if (access(p->argv[0], X_OK) != -1)
	{
		g_sh.exitstatus = exec_with_acces(p->argv[0], p, job, env);
		if (g_sh.exitstatus == 0)
			ft_free_process(p);
		return (0);
	}
	return (1);
}

int				execute(t_process *p, t_job *job, char **env, int i)
{
	char		**path;
	char		*exec_line;

	if (ft_strstr(p->argv[0], "/") != NULL)
		if (exec_in_line(p, job, env) == 0)
			return (g_sh.exitstatus);
	if ((path = ft_strsplit(ft_getenv(env, "PATH"), ':')) == NULL)
		return (ft_free_process(p));
	while (path && path[i])
	{
		exec_line = ft_strjoin(path[i++], "/");
		exec_line = ft_strjoin_free(exec_line, p->argv[0], 0);
		if (access(exec_line, X_OK) != -1)
		{
			g_sh.exitstatus = exec_with_acces(exec_line, p, job, env);
			ft_strdel(&exec_line);
			return (clear_execute(path, p));
		}
		ft_strdel(&exec_line);
	}
	sh_error(0, 0, NULL, 3, "command not found: ", p->argv[0], "\n");
	return (clear_execute(path, p));
}

int				execute_run(t_tree *c, t_tree *stop, t_job *job)
{
	t_process	*p;

	p = NULL;
	p = fill_for_exec(c, stop);
	if (p == (void *)1)
		return (-1);
	else if (p && !p->argv)
		return (ft_free_process(p));
	if (job)
		job->process = p;
	else
		current_execute = p;
	if (check_built_in(p) == 0)
	{	
		g_sh.exitstatus = do_built_in(p);
		reset_fd(g_sh.fds, p);
		ft_free_process(p);
		return (g_sh.exitstatus);
	}
	g_sh.exitstatus = -1;
	return (execute(p, job, env_make(ENV_GLOBAL | ENV_TEMP), 0));
}
