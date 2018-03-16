/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_for_jobs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 17:31:28 by maastie           #+#    #+#             */
/*   Updated: 2018/03/16 12:26:40 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern	struct termios	s_termios_backup;
extern	t_cmd_action	g_cmd_actions[];

t_tree			*cpy_from_tree(t_tree *c)
{
	t_tree		*new;
	t_tree		*save;

	new = NULL;
	while (c)
	{
		if (!new)
		{
			new = (t_tree *)ft_memalloc(sizeof(t_tree));
			ft_memcpy(&new->token, &c->token, sizeof(t_token));
			save = new;
		}
		else
		{
			new->right = (t_tree *)ft_memalloc(sizeof(t_tree));
			ft_memcpy(&new->right->token, &c->token, sizeof(t_token));
			new = new->right;
		}
		c = c->right;
	}
	return (save);
}

int				exec_with_acces(char *tmp, t_process *p, t_job *job, char **env)
{
	termcaps_restore_tty();
	launch_process(tmp, p, job, env);
	return (g_sh.exitstatus);
}

void			modify_io_child(t_process *p, int pipe[2][2], int premier, int dernier)
{
	(void)p;
	// if (!premier)
	// {
	// 	DEBUG("\t\t\t\tPREMIER\n");
	// 	DEBUG("p->stdin = %d, p->stdout = %d, p->stderr = %d\n", p->stdin, p->stdout, p->stderr);
	// 	DEBUG("pipe[0][0] = %d, pipe[0][1] = %d\n", pipe[0][0], pipe[0][1]);
	// 	DEBUG("pipe[1][0] = %d, pipe[1][1] = %d\n", pipe[1][0], pipe[1][1]);
	// }
	// if (!dernier)
	// {
	// 	DEBUG("\t\t\t\tDERNIER\n");
	// 	DEBUG("p->stdin = %d, p->stdout = %d, p->stderr = %d\n", p->stdin, p->stdout, p->stderr);
	// 	DEBUG("pipe[0][0] = %d, pipe[0][1] = %d\n", pipe[0][0], pipe[0][1]);
	// 	DEBUG("pipe[1][0] = %d, pipe[1][1] = %d\n", pipe[1][0], pipe[1][1]);
	// }
	if (dernier && premier)
	{
		DEBUG("\t\t\t\tDERNIER  PREMIER\n");
		DEBUG("p->stdin = %d, p->stdout = %d, p->stderr = %d\n", p->stdin, p->stdout, p->stderr);
		DEBUG("pipe[0][0] = %d, pipe[0][1] = %d\n", pipe[0][0], pipe[0][1]);
		DEBUG("pipe[1][0] = %d, pipe[1][1] = %d\n", pipe[1][0], pipe[1][1]);
		if (p->stdin != STDIN_FILENO)
			dup2(p->stdin, STDIN_FILENO);
		if (p->stdout != STDOUT_FILENO)
			dup2(p->stdout, STDOUT_FILENO);
		if (p->stderr != STDERR_FILENO)
			dup2(p->stderr, STDERR_FILENO);
	}
	if (!dernier)
	{
		if (p->stdout != STDOUT_FILENO)
		{
			dup2(p->stdout, STDOUT_FILENO);
			close(pipe[1][1]);
		}
		else
			dup2(pipe[1][1], STDOUT_FILENO);
		if (p->stdin != STDIN_FILENO)
			dup2(p->stdin, STDIN_FILENO);
		close(pipe[0][0]);
	}
	if (!premier)	
	{
		if (p->stdin != STDIN_FILENO)
		{
			dup2(p->stdin, STDIN_FILENO);
			close(pipe[1][0]);
		}
		else
			dup2(pipe[1][0], STDIN_FILENO);
		if (p->stdout != STDOUT_FILENO)
			dup2(p->stdout, STDOUT_FILENO);
		close(pipe[0][1]);
	}
	 close(pipe[0][0]);
	 close(pipe[0][1]);
	 close(pipe[1][0]);
	 close(pipe[1][1]);
}

int				executor(t_job *j, t_process *p, int pipe[2][2], char **env)
{
	char		**path;
	char		*exec_line;
	int			i;

	i = 0;
	if (!p->argv)
		exit(EXIT_FAILURE);
	modify_io_child(p, pipe, j->process == p, !p->next);
	if (do_built_in(p, env))
		(void)1;
	// if (ft_strstr(p->argv[0], "/") != NULL)
	// 	if (exec_in_line(j, env) == 0)
	// 		exit(EXIT_FAILURE);
	path = ft_strsplit(ft_getenv(env, "PATH"), ':');
	while (path && path[i])
	{
		exec_line = ft_strjoin(path[i++], "/");
		exec_line = ft_strjoin_free(exec_line, p->argv[0], 0);
		if (access(exec_line, X_OK | F_OK) != -1)
		{
			exec_with_acces(exec_line, p, j, env);
			ft_strdel(&exec_line);
			exit(clear_execute(path, p));// pas de free sur p;
		}
		ft_strdel(&exec_line);
	}
	sh_error(0, 0, NULL, 3, "command not found: ", p->argv[0], "\n");
	clear_execute(path, p);
	exit(EXIT_FAILURE);
}

void			execute_job(t_job *job)
{
	char		**env;

	env = env_make(ENV_GLOBAL | ENV_TEMP);
	if (!job->process->next && do_built_in(job->process, env))
	{
		//A ta sauce le roux 
	}
	else
		execute_job_with_fork(job, env);
}

void			execute_job_with_fork(t_job *j, char **env)
{
	t_process	*pr;
	int			p[2][2];

	pr = j->process;
//	p[1][0] = pr->stdin;
	while (pr)
	{
		if (pr != j->process)
			close(p[1][1]);
		if (pr->next)
		{
			if (pipe(p[0]) == -1)
				return ; //MESSAGE ERREUR;
		}
		p[1][1] = p[0][1];
		if ((pr->pid = fork()) == -1)
			return ; // MESSAGE ERREUR
		if (!pr->pid)
			executor(j, pr, p, env);
		if (!j->pgid)
			j->pgid = pr->pid;
		if (pr != j->process)
			close(p[1][0]);
		p[1][0] = p[0][0];
	// if (STDIN_FILENO != pr->stdin)
	// 	close(pr->stdin);
	// if (STDOUT_FILENO != pr->stdout)
	// 	close(pr->stdout);
		pr = pr->next;
	}
}

t_tree			*next_on_tree(t_tree *c, int exit_status)
{
	if (!c)
		return (NULL);
	if (c->token.id == AND_IF && exit_status != 0)
		c = get_new_from_failure_and(c);
	else if (c->token.id == OR_IF && exit_status == 0)
		c = new_success_or_if(c);
	else
		c = c->right;
	return (c);
}

t_job			*get_new_job(t_tree *c, int exit_status, int fg)
{
	t_job		*job;

	if ((c = next_on_tree(c, exit_status)) == NULL)
		return (NULL);
	job = create_new_job(c);
	job->foreground = fg;
	return (job);
}


t_tree			*fill_process(t_tree *c, t_process *p)
{
	int			i;

	p->stdin = STDIN_FILENO;
	p->stdout = STDOUT_FILENO;
	p->stderr = STDERR_FILENO;
	while (c && (c->token.id != AND_IF && c->token.id != OR_IF
		 && c->token.id != PIPE))
	{
		i = -1;
		while (c && g_cmd_actions[++i].fjob)
		{
			if (g_cmd_actions[i].one == c->token.id)
			{
				c = g_cmd_actions[i].fjob(p, c);
				if (c == (void *)1)
					return ((void *)1);
				i = -1;
			}
		}
	}
	return (c);
}

int				fill_job(t_tree *c, t_job *j)
{
	t_process 	*new;
	t_process	**tmp;

	tmp = &j->process;
	while (c && (c->token.id != AND_IF && c->token.id != OR_IF))
	{
		if (c->token.id == PIPE)
			c = c->right;
		new = ft_memalloc(sizeof(t_process));
		*tmp = new;
		tmp = &new->next;
		c = fill_process(c, new);
		if (c && c->token.id != PIPE)
			j->finish_command = cpy_from_tree(c);
		else
			j->finish_command = NULL;
	}
	return (0);
}

t_job			*create_new_job(t_tree *c)
{
	t_job 		*job;
	t_list		*new_order;
	t_tree		*tmp;

	if (c == NULL || c == (void *)1)
		return (NULL);
	tmp = c;
	job = (t_job *)ft_memalloc(sizeof(t_job));
	new_order = ft_lstnew(NULL, 0);
	new_order->content = job;
	new_order->next = g_job_order;
	g_job_order = new_order;
	job->command = get_command(job->command, c);
	job->num = get_id_max_job();
	job->tmodes = s_termios_backup;
	job->foreground = 1;
	while (tmp->right)
		tmp = tmp->right;
	if (tmp->token.id == AND && g_sh.subshellactive == 1)
		tmp->token.id = SEMI;
	else if (tmp->token.id == AND)
		job->foreground = 0;
	fill_job(c, job);
	return (job);
}

int 			wait_osef_exec(t_process *p)
{
	int ret;

	ret = -1;
	while (p)
	{
		waitpid(p->pid, &ret, 0);
		p = p->next;
	}
	return (ret);
}

int				ft_fill_for_jobs(t_tree *head)
{
	t_tree		*tmp;
	t_job		*tmp2;
	int 		ret;

	tmp = head;
	while (tmp)
	{
		tmp2 = create_new_job(tmp);
		while (tmp2)
		{
			execute_job(tmp2);
			ret = wait_osef_exec(tmp2->process);
			termcaps_set_tty();
			tmp2 = get_new_job(tmp2->finish_command, ret, 1);
		}
		tmp = tmp->left;
	}
	//ft_free_order(g_job_order);
	//return (ft_free_tree(head));
	return (0);
}
