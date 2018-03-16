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

// t_tree				*check_and_do_pipe(t_tree *c, t_job *job, t_list *lst)
// {
// 	t_tree			*tmp;
// 	t_tree			*ret;
// 	t_job			*tmp2;

// 	tmp = c;
// 	while (tmp)
// 	{
// 		if (tmp->token.id == AND_IF || tmp->token.id == OR_IF)
// 			return (c);
// 		else if (tmp->token.id == PIPE)
// 		{
// 			while (tmp && tmp->right && (tmp->token.id != AND_IF && tmp->token.id != OR_IF))
// 				tmp = tmp->right;
// 			ret = tmp;
// 			while (tmp && tmp->previous && tmp->previous->token.id != PIPE)
// 				tmp = tmp->previous;
// 			!ret->right ? ret = ret->right : 0;
// 			job->finish_command = ret;
// 			lst->next = g_job_order;
// 			g_job_order = lst;
// 			tmp2 = g_first_job;
// 			while (tmp2 && tmp2->next)
// 				tmp2 = tmp2->next;
// 			if (tmp2)
// 				tmp2->next = job;
// 			else
// 				g_first_job = job;
// 			if (job->foreground)
// 			// termcaps_restore_tty();
// 			// do_pipe(c, tmp, job);
// 			// termcaps_set_tty();
// 			return (ret);
// 		}
// 		tmp = tmp->right;
// 	}
// 	return (c);
// }

// t_tree 			*init_new_job(t_tree *c)
// {
// 	t_job 		*job;
// 	t_list		*new_order;
// 	t_tree		*tmp;

// 	tmp = c;
// 	job = (t_job *)ft_memalloc(sizeof(t_job));
// 	new_order = ft_lstnew(NULL, 0);
// 	new_order->content = job;
// 	job->command = get_command(job->command, c);
// 	job->num = get_id_max_job();
// 	// A MODIFIRE POUR L ORDRE DES JOB TEST IS FOR FREE
// 	new_order->next = g_job_order;
// 	g_job_order = new_order;
// 	job->foreground = 1;
// 	job->process = (t_process *)ft_memalloc(sizeof(t_process));
// 	job->free_process = job->process;
// 	job->process->stdout = 1;
// 	job->process->stderr = 2;
// 	while (tmp->right)
// 		tmp = tmp->right;
// 	if (tmp->token.id == AND)
// 	{
// 		if (g_sh.subshellactive == 1)
// 			tmp->token.id = SEMI;
// 		else
// 			job->foreground = 0;
// 	}
// 	return (execute_run(c, job));
// }

// t_tree				*execute_run(t_tree *c, t_job *job, t_list *lst)
// {
// 	t_tree			*tmp;

// 	tmp = c;

// 	// while (tmp)
// 	// {
// 		tmp = check_and_do_pipe(tmp, job, lst);
// 		if (tmp && (tmp->token.id != AND_IF && tmp->token.id != OR_IF))
// 			if ((tmp = cmd_action(tmp, job, lst)) == ((void *)1))
// 				return (tmp);
// 		// if (tmp)
// 		// {
// 		// 	DEBUG("IF TMP  == %s\n", tmp->token.str);
// 		// 	if (tmp && tmp->token.id == AND_IF && job->process->status != 0)
// 		// 	{
// 		// 		if ((tmp = get_new_from_failure_and(tmp)) == NULL)
// 		// 			return (tmp);
// 		// 	}
// 		// 	else if (tmp->token.id == OR_IF && job->process->status == 0)
// 		// 		tmp = new_success_or_if(tmp);
// 		// 	else
// 		// 		tmp = tmp->right;
// 		// }
// 		// if (job)
// 		// {
// 		// 	g_current_process->finish_oni = tmp;
// //		job->finish_command = tmp;
// 		// if (tmp)
// 		// 	return (init_new_job(tmp));
// 	// }
// 	return (tmp);
// }

// t_tree			*cmd_action(t_tree *c, t_job *job, t_list *lst)
// {
// 	int			i;
// 	t_tree		*tmp;
// //	char		**env;	
// 	// t_job		*tmp2;

// 	tmp = c;
// 	i = -1;
// 	while (c && g_cmd_actions[++i].fjob)
// 	{
// 		if (c && (c->token.id == OR_IF || c->token.id == AND_IF))
// 			break ;
// 		if (c && g_cmd_actions[i].one == c->token.id)
// 		{
// 			c = g_cmd_actions[i].fjob(job->process, c);
// 			if (c == (void *)1)
// 				return ((void *)1);
// 			i = -1;
// 		}
// 	}
/*	env = env_make(ENV_GLOBAL | ENV_TEMP);
	job->finish_command = c;
	set_fd(job->process);
	if (do_built_in(job->process, env))
	{
		ft_memdel((void**)&lst);
		del_job(job); 
	}
	else
	{
		lst->next = g_job_order;
		g_job_order = lst;

		tmp2 = g_first_job;
		while (tmp2 && tmp2->next)
			tmp2 = tmp2->next;
		if (tmp2)
			tmp2->next = job;
		else
			g_first_job = job;
		execute(job, env, 1); // virer le t_process vue au on a le job
	}
	reset_fdd(job->process); // A virer
*/
//	return (c);
//}

// t_tree			*cpy_from_tree(t_tree *c)
// {
// 	t_tree		*new;

	
// }

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

void			modify_io_child(t_process *p, int pipe[2], int stdin, int stdout, int premier, int dernier)
{
	(void)p;
	if (!dernier)
	{
			DEBUG("dernier Dup2=%d|\n", dup2(stdout, STDOUT_FILENO));
			DEBUG("dernier Dup2=%d|\n", close(pipe[0]));		
	}
	if (!premier)	
	{
			DEBUG("1er Dup2=%d|\n", dup2(stdin, STDIN_FILENO));	
			DEBUG("1er Close=%d|\n", close(pipe[1]));
	}
	 close(pipe[0]);
	 close(pipe[1]);
	 close(stdin);
	 close(stdout);
}

int				executor(t_job *j, t_process *p, int pipe[2], int stdin, int stdout, char **env)
{
	char		**path;
	char		*exec_line;
	int			i;

	i = 0;

	if (!p->argv)
		exit(EXIT_FAILURE);
	modify_io_child(p, pipe, stdin, stdout, j->process == p, !p->next);
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

void			clean_up_io(t_process *p, int fd[2])
{
	DEBUG("CLEAN UP // fd[0] = %d | fd[1] = %d|\n",fd[0], fd[1]);
	// if (p->stdin != STDIN_FILENO)
	// 	close(p->stdin);
	// if (p->stdout != STDOUT_FILENO)
	// 	close(p->stdout);
	// if (p->stderr != STDERR_FILENO)
	// 	close(p->stderr);
	(void)p;
	if (fd[0] > 0)
		close(fd[0]);
	if (fd[1] > 0)
		close(fd[1]);
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
	int			p[2];
	int 		stdin;
	int 		stdout;

	pr = j->process;
	while (pr)
	{
		if (pr != j->process)
			close(stdout);
		if (pr->next)
		{
			if (pipe(p) == -1)
			{
				DEBUG("\n\tYolooooo pipe\n");
				return ; //MESSAGE ERREUR;
			}
			else
				DEBUG("Pipe[0]=%d | [1]=%d|\n", p[0], p[1]);
		}
		stdout = p[1];
		if ((pr->pid = fork()) == -1)
			return ; // MESSAGE ERREUR
		if (!pr->pid)
		{
			executor(j, pr, p, stdin, stdout, env);
			DEBUG("\t\nYolo\n")
		}
		if (!j->pgid)
			j->pgid = pr->pid;
		if (pr != j->process)
			close(stdin);
		stdin = p[0];
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
			j->finish_command = cpy_from_tree(c); // A remplacer par une copie de l'arbre
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
// 	t_process *tmp8;

// 	tmp8 = job->process;
// 	int i;
// 	while (tmp8)
// 	{
// 		i = 0;
// 		while (tmp8->argv[i])
// 		{
// 			DEBUG("[%d][%s]\n", i, tmp8->argv[i]);
// 			i++;
// 		}
// //		DEBUG("\n");
// 		tmp8 = tmp8->next;
// 	}
// 	DEBUG("SORTIE\n");
	return (job);
}

int 			wait_osef_exec(t_process *p)
{
	int ret;

	ret = -1;
	while (p)
	{
		DEBUG("J'attend [%s]\n", p->argv[0]);
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
			DEBUG("tkkn=%s|\n", tmp2->process->argv[0]);
//			sleep(5);
			tmp2 = get_new_job(tmp2->finish_command, ret, 1);
		}
		tmp = tmp->left;
	}
	//ft_free_order(g_job_order);
	//return (ft_free_tree(head));
	return (0);
}
