/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:43:49 by maastie           #+#    #+#             */
/*   Updated: 2018/03/14 21:03:20 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

//extern	t_cmd_action	g_cmd_actions[];

// t_tree			*get_next_pipe(t_tree *c, t_job *job)
// {
// 	t_tree		*tmp;

// 	tmp = c;
// 	while (tmp)
// 	{
// 		if (tmp->token.id == PIPE)
// 		{
// 			init_current_process(tmp, job);
// 			return (tmp->right);
// 		}
// 		tmp = tmp->right;
// 		if (tmp && (tmp->token.id == OR_IF || tmp->token.id == AND_IF))
// 			break ;
// 	}
// 	return (tmp);
// }

// int				execute_pipe_run(t_tree *c, t_job *job)
// {
// 	t_tree		*tmp;
// 	int			i;

// 	i = 0;
// 	tmp = c;
// 	while (c && g_cmd_actions[i].fjob)
// 	{
// 		if (c && (c->token.id == PIPE || c->token.id == AND_IF || c->token.id == OR_IF))
// 			break ;
// 		if (c && g_cmd_actions[i].one == c->token.id)
// 		{
// 			c = g_cmd_actions[i].fjob(job->process, c);
// 			if (c == (void *)1)
// 				return (-1);
// 			i = -1;
// 		}
// 		i++;
// 	}
// 	set_fd(job->process);
// 	if (do_built_in(job->process, env_make(ENV_GLOBAL | ENV_TEMP)) == 0)
// 		execute(job, env_make(ENV_GLOBAL | ENV_TEMP), 0);
// 	reset_fdd(job->process);
// 	return (job->process->status);
// }

// void 			do_pipe(t_tree *c, t_tree *end, t_job *job)
// {
// 	pid_t		f;
// 	int			p[2][2];
// 	t_list		*pid_list;

// 	ft_memset(p, -1, sizeof(p));
// 	pid_list = NULL;
// 	while (c)
// 	{
// 		if ((f = (init_pipe_run(f, p, c, end))) == -1)
// 			return ;
			
// 		if (!f)
// 		{
// 			job->pgid == 0 ? setpgid(getpid(), getpid()) : setpgid(getpid(), job->pgid);
// 			DEBUG("MY PGID : %d\n", getpgid(getpid()));
// 			dup_and_close_son_pipe(c, end, p, pid_list);
//  		 	exit(execute_pipe_run(c, job));
// 		}
// 		if (job->pgid == 0)
// 		{
// 			job->pgid = f;
// 			setpgid(f, job->pgid);
// 			if (job->foreground == 1)
// 			{
// 				DEBUG("ret du tcsetpgrp %d\n", tcsetpgrp(g_shell_terminal, job->pgid));
// 			}
// 		}
// 		setpgid(f, job->pgid);
// 		((p[1][0] >= 0 && close(p[1][0])) || 1) && p[1][1] >= 0 && close(p[1][1]);
// 		ft_lst_pushend(&pid_list, ft_lstnew(&f, sizeof(pid_t)));
// 		p[1][0] = p[0][0];
// 		//close_pipe_heredoc(c);
// 		if (c == end)
// 			break ;
// 		c = get_next_pipe(c, job);
// 	}
// 	g_sh.exitstatus = 0;
// 	if (job->foreground == 1)
// 	{
// 		//wait_multiple_proc(pid_list, job);
// 		wait_for_job(job);
// 		tcsetpgrp(g_shell_terminal, g_shell_pgid);
// 		tcgetattr(g_shell_terminal, &job->tmodes);
// 		termcaps_set_tty();
// 	}
// 	else
// 		dprintf(g_sh.fd_tty, "[%d] NEED PID DU LAST PIPE\n", job->num);
// 	ft_lstdel(&pid_list, NULL);
// }
