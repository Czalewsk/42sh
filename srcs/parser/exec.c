/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:54:12 by maastie           #+#    #+#             */
/*   Updated: 2018/02/24 20:54:12 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern	t_fill_job	g_fill_jobs[];

t_process 		*fill_for_exec(t_tree *c, t_tree *stop)
{
	int			i;
	t_process 	*p;

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

int				exec_with_acces(char *tmp, t_process *p, t_job *job)
{
	pid_t		father;

	if ((father = fork()) == -1)
		exit(-1);
	if (father == 0)
	{
		if (job)
		{
//			ft_printf("exec.c 53\n");
			p->pid = getpid();
			job->pgid = setpgid(getpid(), getpid());
		}
		exit(g_sh.exitstatus = execve(tmp, p->argv, g_sh.env));
	}
	else
		waitpid(father, &g_sh.exitstatus, WUNTRACED | WCONTINUED);
	return (g_sh.exitstatus);
}

int				execute(t_process *p, t_job *job)
{
	char		**path;
	char		*exec_line;
	int			i;

	i = 0;
	path = ft_strsplit("/Users/maastie/.brew/bin:/Users/maastie/.brew/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/opt/X11/bin:/Applications/VMware", ':');
	while (path && path[i])
	{
		exec_line = ft_strjoin(path[i], "/");
		exec_line = ft_strjoin_free(exec_line, p->argv[0], 0);
		if (access(exec_line, X_OK) != -1)
		{
			g_sh.exitstatus = exec_with_acces(exec_line, p, job);
			ft_strdel(&exec_line);
			break ;
		}
		ft_strdel(&exec_line);
		i++;
	}
	ft_free_array(path);
	reset_fd(g_sh.fds, p);
	ft_free_process(p);
	return (g_sh.exitstatus);
}

int				execute_run(t_tree *c, t_tree *stop, t_job *job)
{
	// char		**path;
	// char		*exec_line;
	// int			i;
	t_process 	*p;

//	i = 0;
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
		return (do_built_in(p));
	return (execute(p, job));
	// g_sh.exitstatus = -1;
	// path = ft_strsplit("/Users/maastie/.brew/bin:/Users/maastie/.brew/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/opt/X11/bin:/Applications/VMware", ':');
	// while (path && path[i])
	// {
	// 	exec_line = ft_strjoin(path[i], "/");
	// 	exec_line = ft_strjoin_free(exec_line, p->argv[0], 0);
	// 	if (access(exec_line, X_OK) != -1)
	// 	{
	// 		g_sh.exitstatus = exec_with_acces(exec_line, p, job);
	// 		ft_strdel(&exec_line);
	// 		break ;
	// 	}
	// 	ft_strdel(&exec_line);
	// 	i++;
	// }
	// ft_free_array(path);
	// reset_fd(g_sh.fds, p);
	// ft_free_process(p);
	// return (g_sh.exitstatus);
}