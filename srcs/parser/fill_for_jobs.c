/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_for_jobs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 17:31:28 by maastie           #+#    #+#             */
/*   Updated: 2018/03/11 18:36:48 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern	t_cmd_action	g_cmd_actions[];

void			set_fd(t_process *p)
{
//	ft_printf("BEFORE EXEC TEST_fd == %d && fd_TTY ==  %d\n", g_sh.test_fd, g_sh.fd_tty);
//	DEBUG("SET FD\np->stdin == %d\np->stdout ==%d\np->stderr ==%d\n", p->stdin, p->stdout, p->stderr);
	if (p->stdin != STDIN_FILENO)
	{
	//		DEBUG("STDIN MIDIFIED\n", p->stdin);
//		close(STDIN_FILENO);
//		ft_printf("B4 p->STDIN == %d && STDIN ==  %d\n", p->stdin, STDIN_FILENO);
		dup2(p->stdin, STDIN_FILENO);
//		ft_printf("AFTER p->STDIN == %d && STDIN ==  %d\n", p->stdin, STDIN_FILENO);
	}
	if (p->stdout != STDOUT_FILENO)
	{
//		DEBUG("STDOUT MIDIFIED\n", p->stdout);
//		ft_printf("B p->STDOUT == %d && STDOUT ==  %d\n", p->stdout, STDOUT_FILENO);
		close(STDOUT_FILENO);
		dup2(p->stdout, STDOUT_FILENO);
//		ft_printf("AFT p->STDOUT == %d && STDOUT ==  %d\n", p->stdout, STDOUT_FILENO);
	}
	if (p->stderr != STDERR_FILENO)
	{
//			DEBUG("STDERR MIDIFIED\n", p->stderr);
		close(STDERR_FILENO);
//		ft_printf("B4 p->STDERR == %d && STDERR ==  %d\n", p->stderr, STDERR_FILENO);
		dup2(p->stderr, STDERR_FILENO);
//		ft_printf("AAFTER p->STDERR == %d && STDERR ==  %d\n", p->stderr, STDERR_FILENO);
	}
//	DEBUG("END SET FD\np->stdin == %d\np->stdout ==%d\np->stderr ==%d\n", p->stdin, p->stdout, p->stderr);
}

void		reset_fdd(t_process *p)
{
//	DEBUG("RESET FD\np->stdin == %d\np->stdout ==%d\np->stderr ==%d\n", p->stdin, p->stdout, p->stderr);
//	DEBUG("STDstdin == %d\nSTDstdout ==%d\nSTDstderr ==%d\n", STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);
	// if (p->stdin != STDIN_FILENO)
	// {
	// 	ft_printf("B4 p->STDIN == %d && STDIN ==  %d\n", p->stdin, STDIN_FILENO);
		close(p->stdin);
		dup2(g_sh.fds[0], STDIN_FILENO);
//		ft_printf("AFTER p->STDIN == %d && STDIN ==  %d\n", p->stdin, STDIN_FILENO);
//	}
	// if (p->stdout != STDOUT_FILENO)
	// {
	// 	ft_printf("B4 p->STDOUT == %d && STDOUT ==  %d\n", p->stdout, STDOUT_FILENO);
		close(p->stdout);
		dup2(g_sh.fds[1], STDOUT_FILENO);
//		dup2(p->stdout, 1);
	// 	if (fcntl(STDOUT_FILENO, F_GETFD) == -1)
	// 		dup(STDOUT_FILENO);
	// 		ft_printf("AFTER p->STDOUT == %d && STDOUT ==  %d\n", p->stdout, STDOUT_FILENO);
	// }
//	if (p->stderr != STDERR_FILENO)
	//{
//		ft_printf("B4 DUP p->STDERR == %d && STDERR ==  %d\n", p->stderr, STDERR_FILENO);
		close(p->stderr);
		dup2(g_sh.fds[2], STDERR_FILENO);
		//	dup2(g_sh.fds[2], STDERR_FILENO);
//		dup2(p->stderr, 2);
		// close(p->stderr);
//		ft_printf("After DUP  p->STDERR == %d && STDERR ==  %d\n", p->stderr, STDERR_FILENO);
//	}
//	ft_printf(" AFTER EXEC TEST_fd == %d && fd_TTY ==  %d\n", g_sh.test_fd, g_sh.fd_tty);
}

int				exec_with_acces(char *tmp, t_process *p, t_job *job, char **env)
{
	pid_t		father;
	int			i;

	DEBUG("CALL TERM RESTORE\n");
	termcaps_restore_tty();
	if ((father = fork()) == -1)
		exit(-1);
	i = 0;
	if (father == 0)
	{
		set_fd(p);
		if (job)
			setpgid(getpid(), getpid());// je suis pas sur que ca reste
			DEBUG("EXCVE  de la CMD\n");
			exit(execve(tmp, p->argv, env));
//			exit(EXIT_FAILURE);
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
//	reset_fdd(p);
	DEBUG("CALL TERM SET\n");
	termcaps_set_tty();
	return (g_sh.exitstatus);
}

int				exec_with_acces_no_fork(char *tmp, t_process *p, t_job *job, char **env)
{

	(void)job;
	DEBUG("EXEC WITH NO FORK\n");
	// termcaps_restore_tty();
	// set_fd(p);
	exit(execve(tmp, p->argv, env));
	// exit(EXIT_FAILURE);
}

int		exec_in_line(t_process *p, t_job *job, char **env)
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
//			sh_error(0, 0, NULL, 3, "execve failed: ", p->argv[0], "\n");
//			ft_free_array(path);
//			exit(EXIT_FAILURE);
			return (clear_execute(path, p));// pas de free sur process;
		}
		ft_strdel(&exec_line);
	}
	sh_error(0, 0, NULL, 3, "command not found: ", p->argv[0], "\n");
	p->returned = -1;
	return (clear_execute(path, p));// pas de free sur process;
}


t_tree			*get_next_pipe(t_tree *c)
{
	t_tree		*tmp;

	tmp = c;
	while (tmp)
	{
		if (tmp->token.id == PIPE)
			return (tmp->right);
		tmp = tmp->right;
	}
	if (tmp && tmp == c)
		return (tmp->right);
	return (tmp);
}

int		execute_pipe_run(t_tree *c, t_job *job)
{
	t_tree	*tmp;
	int			i;

	i = 0;
	tmp = c;
	while (c && g_cmd_actions[i].fjob)
	{
		if (c && (c->token.id == PIPE
			|| c->token.id == AND_IF || c->token.id == OR_IF))
			break ;
		if (c && g_cmd_actions[i].one == c->token.id)
		{
			c = g_cmd_actions[i].fjob(current_process, c);

			if (c == (void *)1)
				return (-1);
			i = -1;
		}
		i++;
	}
	// termcaps_restore_tty();
	set_fd(current_process);
	if (check_built_in(current_process) == 0)
		do_built_in(current_process);
	else
		execute(current_process, job, env_make(ENV_GLOBAL | ENV_TEMP), 0);
	reset_fdd(current_process);
	// termcaps_restore_tty();
	// termcaps_set_tty();
	return (current_process->returned);
}

void				wait_multiple_proc(t_list *pid_list)
{
	while (pid_list)
	{
		if (waitpid(*(pid_t*)pid_list->content,
					&current_process->returned, 0) == -1)
			DEBUG("Erreur waitpid %s| 2\n", strerror(errno)) //utiliser sh_error
				pid_list = pid_list->next;
	}
}

void				init_current_process(void)
{
	current_process->next = (t_process *)ft_memalloc(sizeof(t_process));
	current_process = current_process->next;
	current_process->stdout = 1;
	current_process->stderr = 2;
}

/*
void				do_pipe_child(t_tree *c, int temp[2], int p[2], int i,
		t_job *job)
{
	if (i & 1)
		dup_and_close(temp[1], STDOUT_FILENO, unused);
	if (i & 2)
		dup_and_close(temp[0], STDIN_FILENO, temp[1]);
	exit(execute_pipe_run(c, job));
}
*/

void 				do_pipe(t_tree *c, t_tree *end, t_job *job)
{
	pid_t			f;
	int				p[2];
	t_list			*pid_list;
	int				temp[2];

	temp[1] = -1;
	pid_list = NULL;
	while (c)
	{
		close(temp[1]);
		if (c != end && pipe(p) == -1)
			return ;         // MSG d'erreur
		temp[1] = p[1];
		if ((f = fork()) == -1)
			return ;         // MSG d'erreur
		if (!f)
		{
			if (c != end)
				dup_and_close(temp[1], STDOUT_FILENO, p[0]);
			if (pid_list)
				dup_and_close(temp[0], STDIN_FILENO, p[1]);
 		 	exit(execute_pipe_run(c, job));
		}
		(close(temp[0]) || 1) && close(temp[1]);
		ft_lst_pushend(&pid_list, ft_lstnew(&f, sizeof(pid_t)));
		temp[0] = p[0];
		if (c == end)
			break ;
		c = get_next_pipe(c);
		init_current_process();
	}
	wait_multiple_proc(pid_list);
	ft_lstdel(&pid_list, NULL);
}

t_tree			*new_success_or_if(t_tree *c)
{
	while (c)
	{
		if (c->token.id == AND_IF)
			return (c);
		c = c->right;
	}
	return (c);
}

t_tree			*check_and_do_pipe(t_tree *c, t_job *job)
{
	t_tree		*tmp;
	t_tree		*ret;

	tmp = c;
	while (tmp)
	{
		if (tmp->token.id == AND_IF || tmp->token.id == OR_IF)
			return (c);
		else if (tmp->token.id == PIPE)
		{
			while (tmp && tmp->right && (tmp->token.id != AND_IF && tmp->token.id != OR_IF))
				tmp = tmp->right;
			ret = tmp->right;
			while (tmp && tmp->previous && tmp->previous->token.id != PIPE)
				tmp = tmp->previous;
			termcaps_restore_tty();
			do_pipe(c, tmp, job);
			termcaps_set_tty();
			return (ret);
		}
		tmp = tmp->right;
	}
	return (c);
}

t_tree			*execute_run(t_tree *c, t_job *job)
{
	t_tree		*tmp;
	t_process	*n;

	tmp = c;
	while (tmp)
	{
		tmp = check_and_do_pipe(tmp, job);
		if (tmp && (tmp->token.id != AND_IF && tmp->token.id != OR_IF))
			if ((tmp = cmd_action(tmp, job)) == ((void *)1))
				return (tmp);
		if (tmp)
		{
			DEBUG("current->returned = %d\ng_sh.exitstatus = %d\n", current_process->returned, g_sh.exitstatus);
			if (tmp && tmp->token.id == AND_IF && current_process->returned != 0)
				return ((void *)1);
			else if (tmp->token.id == OR_IF && current_process->returned == 0)
				tmp = new_success_or_if(tmp);
			else
				tmp = tmp->right;
//			ft_free_process(current_process);
		}
		if (tmp)
		{
			n = (t_process *)ft_memalloc(sizeof(t_process));
//			DEBUG("ADDRESEs current %p ,current->next %p\n", current_process, current_process->next);
			current_process->next = n;
			n->stdin = 0;
			n->stdout = 1;
			n->stderr = 2;
			current_process = n;
		}
	}
	return (c);
}

t_tree		*cmd_action(t_tree *c, t_job *job)
{
	int			i;
	t_tree	*tmp;

	tmp = c;
	i = 0;
	while (c && g_cmd_actions[i].fjob)
	{
		if (c && (c->token.id == OR_IF || c->token.id == AND_IF))
			break ;
		if (c && g_cmd_actions[i].one == c->token.id)
		{
			c = g_cmd_actions[i].fjob(current_process, c);
			if (c == (void *)1)
				return ((void *)1);
			i = -1;
		}
		i++;
	}
	if (check_built_in(current_process) == 0)
		do_built_in(current_process);
	else
		execute(current_process, job, env_make(ENV_GLOBAL | ENV_TEMP), 1);
	return (c);
}

t_tree 			*split_and_if_pipe(t_tree *c, t_job *job)
{
	t_process	*free_process; // a mettre en global
	t_tree 		*tmp;

	// METTRE CURRENT_PROCESS EN TMP SAVE DANS SUBSHELL
	tmp = c;
	current_process = (t_process *)ft_memalloc(sizeof(t_process));
	current_process->stdin = 0;
	current_process->stdout = 1;
	current_process->stderr = 2;
	job ? job->process = current_process : current_process;
	free_process = current_process;
	tmp = execute_run(tmp, job);
	ft_free_process(free_process);
	if (tmp == (void *)1)
		return (NULL);
	return (tmp);
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
			tmp->token.id = SEMI;
	}
//	else
//		return (ft_create_jobs(c));
	return (split_and_if_pipe(c, NULL));
}

int				ft_fill_for_jobs(t_tree *head)
{
	t_tree		*tmp;

	tmp = head;
	while (tmp)
	{
//		ft_printf("FILL FOR JOBS %s\n", tmp->token.str);
//		tmp = split_cmd_jobs(tmp);
		if ((split_cmd_jobs(tmp)) == (void *)1)
			break ;
		tmp = tmp->left;
	}
	return (ft_free_tree(head));
}
