/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_for_jobs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 17:31:28 by maastie           #+#    #+#             */
/*   Updated: 2018/03/18 20:00:54 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern	struct termios	s_termios_backup;
extern	t_cmd_action	g_cmd_actions[];

t_tree			*cpy_from_tree(t_tree *c)
{
	t_tree		*new;
	t_tree		*trash;
	t_tree		*save;

	new = NULL;
	while (c)
	{
		if (!new)
		{
			new = (t_tree *)ft_memalloc(sizeof(t_tree));
			new->token.str = ft_strdup(c->token.str);
			new->token.id = c->token.id;
			new->token.size = c->token.size;
			save = new;
//			DEBUG("OLD = %p, NEW = %p\n", c, new);
			
		}
		else
		{
			new->right = (t_tree *)ft_memalloc(sizeof(t_tree));
			new->right->token.str = ft_strdup(c->token.str);
			new->right->token.id = c->token.id;
			new->right->token.size = c->token.size;
//			new->token = c->token;
			new = new->right;
		}
		//		DEBUG("OLD = %p, NEW = %p\n", c, new);
		trash = c;
		c = c->right;
		// ft_strdel(&trash->token.str);
		// free(trash);
	}
	return (save);
}

int				exec_with_acces(char *tmp, t_process *p, t_job *job, char **env)
{
	if (job->foreground)
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
			dup2(p->stdout, STDOUT_FILENO);
		else
			dup2(pipe[1][1], STDOUT_FILENO);
		if (p->stdin != STDIN_FILENO)
			dup2(p->stdin, STDIN_FILENO);
	}
	if (!premier)	
	{
		if (p->stdin != STDIN_FILENO)
			dup2(p->stdin, STDIN_FILENO);
		else
			dup2(pipe[1][0], STDIN_FILENO);
		if (p->stdout != STDOUT_FILENO)
			dup2(p->stdout, STDOUT_FILENO);
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
	if (ft_strstr(p->argv[0], "/") != NULL)
		if (exec_in_line(j, env) == 0)
			exit(EXIT_FAILURE);
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
	// t_job		*tmp;

	if (job == NULL)
		return ;
	env = env_make(ENV_GLOBAL | ENV_TEMP);
	if (!job->process->next  && job->foreground && do_built_in(job->process, env))
	{
		job->is_builtin = 1;
		job->status_last_process = g_sh.exitstatus;
	}
	else
	{
		put_job_at_head_in_job_order(job);
		put_job_at_end_in_first_job(job);
		execute_job_with_fork(job, env);
	}
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
		if (pr->pid && !j->pgid)
		{
			j->pgid = pr->pid;
			setpgid(pr->pid, j->pgid);
			DEBUG("isatty : %d\n", isatty(g_shell_terminal));
			if (j->foreground == 1 && tcsetpgrp(g_shell_terminal, j->pgid) == -1)
				exit(sh_error(1, 0, NULL, 1, "Erreur tcsetpgrp launch_process\n"));
		}
		setpgid(pr->pid, j->pgid);	
		if (!pr->pid)
			executor(j, pr, p, env);
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
	(void)fg;
	return (job);
}


t_tree			*fill_process(t_tree *c, t_process *p)
{
	int			i;

	p->stdin = STDIN_FILENO;
	p->stdout = STDOUT_FILENO;
	p->stderr = STDERR_FILENO;
	while (c && (c->token.id != AND_IF && c->token.id != OR_IF
		 && c->token.id != PIPE) && c->token.id != SEMI && c->token.id != AND)
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

int				fill_job(t_tree *cc, t_job *j)
{
	t_process 	*new;
	t_process	**tmp;
	t_tree		*c;
	
	c = cc;
	tmp = &j->process;
	while (c && (c->token.id != AND_IF && c->token.id != OR_IF) && c->token.id != SEMI && c->token.id != AND)
	{
		if (c->token.id == PIPE)
			c = c->right;
		new = ft_memalloc(sizeof(t_process));
		*tmp = new;
		tmp = &new->next;
		c = fill_process(c, new);
		if (c && c->token.id != PIPE)
		{
			if (c->token.id != SEMI && c->token.id != AND)
				j->finish_command = cpy_from_tree(c);			
		}
		else
			j->finish_command = NULL;
	}
	return (0);
}

void			put_job_at_head_in_job_order(t_job *job)
{
	t_list	*new;

	new = ft_lstnew(NULL, 0);
	new->next = g_job_order;
	g_job_order = new;
	new->content = job;
}

void			put_job_at_end_in_first_job(t_job *job)
{
	t_job	*tmp;

	tmp = g_first_job;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = job;
	else
		g_first_job = job;
}

t_job			*create_new_job(t_tree *c)
{
	t_job 		*job;
	t_tree		*tmp;

	if (c == NULL || c == (void *)1)
		return (NULL);
	tmp = c;
	job = (t_job *)ft_memalloc(sizeof(t_job));
	job->command = get_command(job->command, c);
	job->num = get_id_max_job();
	job->tmodes = s_termios_backup;
	job->foreground = 1;
	while (tmp->right && tmp->token.id != AND_IF && tmp->token.id != OR_IF)
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

void	print_process(t_process *p)
{
	int		i;

	if (p == NULL)
	{
		DEBUG("		process p est NULL\n");
		return ;
	}
	DEBUG("		process p a un next : %s\n", p->next != NULL ? "oui" : "non");
	DEBUG("		pid du process : %d\n", p->pid);
	DEBUG("		state du process : %d\n", p->state);
	DEBUG("		status du process : %d\n", p->status);
	DEBUG("		stdin du process : %d\n", p->stdin);
	DEBUG("		stdout du process : %d\n", p->stdout);
	DEBUG("		stderr du process : %d\n", p->stderr);
	DEBUG("		ARGV du process :\n");
	DEBUG("			");
	i = 0;
	while (p->argv[i])
	{
		DEBUG("%s ", p->argv[i]);
		i++;
	}
	DEBUG("\n");
}

void	print_job(t_job *job)
{
	t_process	*tmp;

	if (job == NULL)
	{
		DEBUG("job est NULL\n");
		return ;
	}
	DEBUG("\n\nJOB\n");
	DEBUG("job status_last_process : %d\n", job->status_last_process);
	DEBUG("job num : %d\n", job->num);
	DEBUG("job command : %s\n", job->command);
	DEBUG("job foreground : %d\n", job->foreground);
	DEBUG("job PGID : %d\n", job->pgid);
	DEBUG("job have tree : %s\n", job->finish_command != NULL ? "oui" : "non");
	tmp = job->process;
	while (tmp)
	{
		print_process(tmp);
		tmp = tmp->next;
	}
	DEBUG("\n\n");
}

void	print_first_job()
{
	t_job	*tmp;

	tmp = g_first_job;
	if (tmp == NULL)
	{
		DEBUG("g_first_job est NULL\n");
		return ;
	}
	DEBUG("\n\n\n			PRINT FIRST JOB\n");
	while (tmp)
	{
		print_job(tmp);
		tmp = tmp->next;
	}
	DEBUG("			PRINT FIRST JOB\n\n\n\n");
}

void	print_job_order()
{
	t_list	*tmp;

	tmp = g_job_order;
	if (tmp == NULL)
	{
		DEBUG("g_job_order est NULL\n");
		return ;
	}
	DEBUG("\n\n\n			PRINT JOB ORDER\n");
	while (tmp)
	{
		print_job(tmp->content);
		tmp = tmp->next;
	}
	DEBUG("			PRINT JOB ORDER\n\n\n\n");
}

t_job			*need_norme(t_job *j)
{
	t_job	*res;

	res = get_new_job(j->finish_command, j->status_last_process, j->foreground);
	free_job(j);
	return (res);
}

int				ft_fill_for_jobs(t_tree *head)
{
	t_tree		*tmp;
	t_job		*tmp2;

	tmp = head;
	while (tmp)
	{
		tmp2 = create_new_job(tmp);
		while (tmp2)
		{
			execute_job(tmp2);
			if (!g_shell_is_interactive)
				wait_for_job (tmp2);
			else if (tmp2->is_builtin == 0 && tmp2->foreground)
				tmp2 = put_job_in_foreground(tmp2, 0);
			else if (tmp2->is_builtin == 0)
			{
				put_job_in_background(tmp2, 0);
				tmp2 = NULL;
			}
			else if (tmp2->is_builtin == 1)
				tmp2 = need_norme(tmp2);
		}
		tmp = tmp->left;
	}
	ft_free_tree(head);
	return (0);
}
