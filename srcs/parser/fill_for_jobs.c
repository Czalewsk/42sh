/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_for_jobs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 17:31:28 by maastie           #+#    #+#             */
/*   Updated: 2018/03/16 21:19:23 by scorbion         ###   ########.fr       */
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

int				exec_with_acces(char *tmp, t_process *p, t_job *job, char **env)
{
	if (job->foreground)
		termcaps_restore_tty();
	launch_process(tmp, p, job, env);
	return (g_sh.exitstatus);
}

void			modify_io_child(t_process *p, int in_outfile[2], int premier, int dernier)
{
	// DEBUG("Process = %s | Premier=%d | Dernier = %d|\n", p->argv[0], premier, dernier);
	// DEBUG("p->stdin=%d | p->stdout=%d|\n", p->stdin, p->stdout);
	// DEBUG("in[0]=%d | out[1]=%d\n", in_outfile[0], in_outfile[1]);
	(void)premier;
	(void)dernier;
	if (in_outfile[0] != p->stdin)
		close(in_outfile[0]);
	if (in_outfile[1] != p->stdout)
		close(in_outfile[1]);
//	if (!premier && p->stdout != STDOUT_FILENO)
//		dup_and_close(p->stdout, STDOUT_FILENO, in_outfile[0]);
//	if (!dernier && p->stdin != STDIN_FILENO)
//		dup_and_close(p->stdin, STDIN_FILENO, in_outfile[1]);
}

int				executor(t_job *j, t_process *p, int in_outfile[2], char **env)
{
	char		**path;
	char		*exec_line;
	int			i;

	i = 0;

	if (!p->argv)
		exit(EXIT_FAILURE);
	modify_io_child(p, in_outfile, j->process == p, !p->next);
	(void)in_outfile;
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

void			clean_up_io(t_process *p, int fd[2])
{
	//DEBUG("fd[0] = %d | fd[1] = %d|\n",fd[0], fd[1]);
	if (p->stdin != STDIN_FILENO)
		close(p->stdin);
	if (p->stdout != STDOUT_FILENO)
		close(p->stdout);
	if (p->stderr != STDERR_FILENO)
		close(p->stderr);
	if (fd[0] != STDIN_FILENO)
		close(fd[0]);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
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
		//A ta sauce le roux
		// DEBUG("execute_job : built in executer\n");
		job->is_buildin = 1;
		job->status_last_process = g_sh.exitstatus;
		// tmp = get_new_job(job->finish_command, job->status_last_process, job->foreground);
		// DEBUG("ft_fill_for_jobs : BESOIN DE FREE sur la ligne ref->finish_command = NULL;\n")
		// job->finish_command = NULL;
		
	}
	else
	{
		DEBUG("execute_job : Avant l'appel de execute_job_with_fork\n");
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
	ft_memset(p, -1, sizeof(p));
	p[1][0] = pr->stdin;
	while (pr)
	{
		if (pr->next)
		{
			if (pipe(p[0]) == -1)
				return ; //MESSAGE ERREUR;
			p[1][1] = p[0][1];
		}
		else
			p[1][1] = pr->stdout;
		if ((pr->pid = fork()) == -1)
			return ; // MESSAGE ERREUR
		if (!pr->pid)
			executor(j, pr, p[1], env);
		if (!j->pgid)
			j->pgid = pr->pid;
		clean_up_io(pr, p[1]);
		p[1][0] = p[0][0];
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
		 && c->token.id != PIPE && c->token.id != AND))
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
	while (c && (c->token.id != AND_IF && c->token.id != OR_IF && c->token.id != AND))
	{
		if (c->token.id == PIPE)
			c = c->right;
		new = ft_memalloc(sizeof(t_process));
		*tmp = new;
		tmp = &new->next;
		c = fill_process(c, new);
		if (c && c->token.id != PIPE)
			j->finish_command = c; // A remplacer par une copie de l'arbre
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

int				ft_fill_for_jobs(t_tree *head)
{
	t_tree		*tmp;
	t_job		*tmp2;
	t_job		*tmp3;

	tmp = head;
	while (tmp)
	{
		tmp2 = create_new_job(tmp);
		while (tmp2)
		{
			DEBUG("avant execute\n");
			execute_job(tmp2);
			if (!g_shell_is_interactive)
				wait_for_job (tmp2);
			else if (tmp2->is_buildin == 0 && tmp2->foreground)
			{
				put_job_in_foreground(tmp2, 0);
				tmp2 = NULL;
			}
			else if (tmp2->is_buildin == 0)
			{
				dprintf(g_sh.fd_tty, "[%d] %d\n", tmp2->num, tmp2->process->pid); //LI CONNARD AVANT DE FAIRE LA NORME NEED CHANGER AUTRE QUE DPRINTF
				g_sh.exitstatus = 0;
				put_job_in_background(tmp2, 0);
				tmp2 = NULL;
			}
			else if (tmp2->is_buildin == 1)
			{
				DEBUG("PRE ENCHAINEMENT\n");
				tmp3 = get_new_job(tmp2->finish_command, tmp2->status_last_process, tmp2->foreground);
				DEBUG("%s\n", tmp2->command)
				tmp2->finish_command = NULL;
				if (job_is_completed(tmp2))
					free_job(tmp2);
				tmp2 = tmp3;
				DEBUG("POST ENCHAINEMENT\n")

			}			
		}
		DEBUG("fin boucle interne\n");
		tmp = tmp->left;
	}
	//ft_free_order(g_job_order);
	//return (ft_free_tree(head));

	return (0);
}
