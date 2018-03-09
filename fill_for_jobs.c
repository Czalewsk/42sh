/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_for_jobs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 17:31:28 by maastie           #+#    #+#             */
/*   Updated: 2018/03/06 15:05:45 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

// ajouter le t_list dans le pipe
// et dans g_checkproc

extern	t_token_action	g_token_actions[];
extern	t_cmd_action	g_cmd_actions[];

int				exec_with_acces(char *tmp, t_process *p, t_job *job, char **env)
{
	pid_t		father;
	int			i;

	
	termcaps_restore_tty();
	if ((father = fork()) == -1)
		exit(g_sh.exitstatus = p->returned);
	i = 0;
	if (father == 0)
	{
		if (job)
			setpgid(getpid(), getpid());// je suis pas sur que ca reste
		exit(p->returned = execve(tmp, p->argv, env));
	}
	else
	{
		if (!job)
			while (waitpid(father, &g_sh.exitstatus, WUNTRACED) == -1
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
	termcaps_set_tty();
	return (g_sh.exitstatus);
}

static int		exec_in_line(t_process *p, t_job *job, char **env)
{
	if (access(p->argv[0], X_OK) != -1)
	{
		exec_with_acces(p->argv[0], p, job, env);
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
			return (-1);
	if ((path = ft_strsplit(ft_getenv(env, "PATH"), ':')) == NULL)
		return (ft_free_process(p));//test d exec avec NULL ?
	while (path && path[i])
	{
		exec_line = ft_strjoin(path[i++], "/");
		exec_line = ft_strjoin_free(exec_line, p->argv[0], 0);
		if (access(exec_line, X_OK) != -1)
		{
			exec_with_acces(exec_line, p, job, env);
			ft_strdel(&exec_line);
			return (clear_execute(path, p));// pas de free sur process;
		}
		ft_strdel(&exec_line);
	}
	sh_error(0, 0, NULL, 3, "command not found: ", p->argv[0], "\n");
	return (clear_execute(path, p));// pas de free sur process;
}
int		execute_pipe_run(t_tree *c, t_job *job)
{
	t_tree	*tmp;

	//set_next_procces;
	tmp = c;
	if ((tmp = cmd_action(c, job)) == (void *)1)
		return (tmp);
	//reset_fd(g_sh.fds, p); A METTRE DANS DO_BUILT_IN
	if (check_built_in(current_process) == 0)
		do_built_in(current_process);
	else 
		execute(current_process, job, env_make(ENV_GLOBAL | ENV_TEMP), 0);
	return (g_sh.exitstatus);
}

t_tree			*ft_pipe(t_tree *c, t_job *job)
{
	pid_t		f;
	int			fd[2];

	//set_next_procces;
	if (pipe(fd[2]) == -1 || (f = fork()) == -1)
		return (-1);
	else
	{
		if (f == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			if (c->left && c->left->token.id == PIPE)
				return (ft_pipe(c->left, job));
			return (execute_pipe_run(c->left, job));
		}
		else
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			exit(execute_pipe_run(c, job));
		}
	}
	return (c->left);
}

t_tree			*execute_run(t_tree *c, t_job *job)
{
	t_tree		*tmp;

	if (c->left && c->left->token.id != PIPE)
		{
			if ((tmp = cmd_action(c, job)) == (void *)1)
				return (tmp);
			//reset_fd(g_sh.fds, p); A METTRE DANS DO_BUILT_IN
			if (check_built_in(current_process) == 0)
				do_built_in(current_process);
			else 
				execute(current_process, job, env_make(ENV_GLOBAL | ENV_TEMP), 0);
			current_process->returned = g_sh.exitstatus;
		}
	else
		while (c && c->left && c->left->token.id == PIPE)
			if ((c = ft_pipe(c, job)) == (void *)1)
				return (c);
	if (c->left)
	{
		if (c->left->token.id == AND_IF && g_sh.exitstatus == -1)
			return ((void *)1);
		else if (c->left->token.id == OR_IF && g_sh.exitstatus == 0)
			while (c->left && c->left->token.id == OR_IF)
				c = c->left;
	}
	return (execute_run(c->left, job));
}

t_tree	*cmd_action(t_tree *c, t_job *job)
{
	if (c && (c->token.id == PIPE || c->token.id == OR_IF
			|| c->token.id == AND_IF))
		c = c->right;
	while (c && g_fill_jobs[i].fjob)
	{
		if (c && g_fill_jobs[i].one == c->token.id)
		{
			c = g_fill_jobs[i].fjob(current_process, c);
			if (c == (void *)1)
				return ((void *)1);
			i = -1;
		}
		i++;
	}
	return (c);
}

t_tree	*token_actions(t_tree *c, t_job *job)
{
	t_tree	*tmp;

	c->left ? c->save_left = c->left : c;
	tmp = c;
	while (c)
	{
		if (c->token.id == AND_IF || c->token.id == OR_IF
			|| c->token.id == PIPE)
		{
			c->left = c->right;
			c->right = NULL;
			c = c->left;
		}
		c ? c = c->right : c;
	}
	return (execute_run(tmp, job));
}

t_tree 			*split_and_if_pipe(t_tree *c, t_job *job)
{
	t_tree 		*tmp;
	t_process	*free_process;

	tmp = c;
	// METTRE CURRENT_PROCESS EN TMP SAVE DANS SUBSHELL
	current_process = (t_process *)ft_memalloc(sizeof(t_process));
	job ? job->process = current_process; current_process;
	free_process = current_execute;
	tmp = token_actions(tmp, job);
	//ft_rebuild_tree_for_free;
	ft_free_process(free_process);
	if (tmp == (void *)1)
		return (NULL);
	if (c->save_left)
		c = c->save_left;
	return (c->left);
}

t_tree			*split_cmd_jobs(t_tree *c)
{
	t_tree		*tmp;

	tmp = c;
	while (tmp->right)
		tmp = tmp->right;
	if (tmp->token.id == AND && g_sh.subshellactive == 1)
	{
			// ft_strdel(&tmp->token.id);
			// tmp->token.id = ft_strdup(";");
			tmp->token.id == SEMI;
	}
	else
		return (ft_create_jobs(c));
	return (split_and_if_pipe(c, NULL));
}

int				ft_fill_for_jobs(t_tree *head)
{
	t_tree		*tmp;

	tmp = head;
	while (tmp)
		tmp = split_cmd_job(tmp);
	return (ft_free_tree(head));
}
