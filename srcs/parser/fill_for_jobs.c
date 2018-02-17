/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_for_jobs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 17:31:28 by maastie           #+#    #+#             */
/*   Updated: 2018/01/02 17:31:28 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern	t_fill_job	g_fill_jobs[];
extern  t_check_proc g_check_procs[];

int	returned;
int closefd[3];

t_process 		*fill_for_exec(t_tree *c, t_tree *stop)
{
	int	i;
	t_process 	*p;

	i = 0;
	p = NULL;
	p = init_process(p);
	// if (!stop)
	// 	c  = g_fill_jobs[0].fjob(p, c); enlever pour la redirection 2>&1 
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

int		exec_acces(char *tmp, t_process *p, t_job *job)
{
	pid_t	father;

	(void)job;
	if ((father = fork()) == -1)
		exit(-1);
	if (father == 0)
	{
		if (job)
		{
			p->pid = getpid();
			job->pgid = setpgid(getpid(), getpid());
		}

//		cjob->pgid = setgpid(p->pid, p->pid);
		exit(returned = execve(tmp, p->argv, g_sh.env));
	}
	else
		waitpid(father, &returned, WUNTRACED | WCONTINUED);
	return (returned);
}

int		execute_run(t_tree *c, t_tree *stop, t_job *job)
{
	char		**path;
	char		*exec_line;
	int			i;
	t_process 	*p;

	i = 0;
	p = NULL;
	p = fill_for_exec(c, stop);
	if (p == (void *)1)
		return (-1);
	if (job)// command avec &
		job->process = p;
	else
		current_execute = p; // simple command avec possibilite de la mettre en bg
	returned = -1;
	path = ft_strsplit("/Users/maastie/.brew/bin:/Users/maastie/.brew/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/opt/X11/bin:/Applications/VMware", ':');
	while (path && path[i])
	{
		exec_line = ft_strjoin(path[i], "/");
		exec_line = ft_strjoin_free(exec_line, p->argv[0], 0);
		if (access(exec_line, X_OK) != -1)
		{
			ft_printf("\n");
			returned = exec_acces(exec_line, p, job);
			ft_strdel(&exec_line);
			break ;
		}
		ft_strdel(&exec_line);
		i++;
	}
	ft_free_array(path);
	reset_fd(closefd, p);
	ft_free_process(p);
	return (returned);
}

t_tree *get_new_process_from_valid_or_if(t_tree *c)
{
	while (c)
	{
		c = c->right;
		if (c && c->token.id == AND_IF)
			return (c->right);
	}
	return (c);
}

t_tree *get_new_process_from_pipe(t_tree *c)
{
	while (c)
	{
		c = c->right;
		if (c && c->token.id == AND_IF)
		{
			if (returned == -1)
				return (NULL);
			return (c->right);
		}
		else if (c && c->token.id == OR_IF)
		{
			if (returned == 0)
				return(c = get_new_process_from_valid_or_if(c));
			return (c->right);
		}
	}
	return (c);
}

t_tree	*check_or_if(t_tree *tmp, t_tree *stop)
{
	if ((returned = execute_run(tmp, stop, NULL)) == 0)
		return (tmp = get_new_process_from_valid_or_if(stop->right));
	return (stop->right);
}

t_tree	*check_and_if(t_tree *tmp, t_tree *stop)
{
	if ((returned = execute_run(tmp, stop, NULL)) != 0)
		return ((void *)1);
	return (stop->right);
}

t_tree	*check_pipe(t_tree *tmp, t_tree *stop)
{
	if (set_for_pipe(tmp) == 0)
		return (tmp = get_new_process_from_pipe(stop));
	return ((void *)1);
}

t_tree	*check_run_v2(t_tree *c)
{
	t_tree	*tmp;
	t_tree	*stop;

	tmp = c;
	stop = c;
	while (stop)
	{
		if (stop->token.id == AND_IF || stop->token.id == OR_IF
			|| stop->token.id == PIPE)
		{
			stop->token.id == AND_IF ? tmp = g_check_procs[0].cproc(tmp, stop) : tmp;
			stop->token.id == OR_IF ? tmp = g_check_procs[1].cproc(tmp, stop) : tmp;
			stop->token.id == PIPE ? tmp = g_check_procs[2].cproc(tmp, stop) : tmp;
			if (tmp == (void *)1)
				return (NULL);
			stop = tmp;
		}
		if (stop && stop->right == NULL)
			returned = execute_run(tmp, stop->right, NULL);
		stop ? stop = stop->right : stop;
	}
	return (c->left);
}

void	fill_for_jobs(t_job *j, t_tree *c)
{
	j->command = get_command(j->command, c);
}

void	add_n_job(t_job *new)
{
	t_job *tmp;

	tmp = first_job;
	while (tmp->next)
		tmp = tmp->next;
	new->num = tmp->num + 1;
	tmp->next = new;
}

void	add_n_order(t_list	*n_order)
{
	t_list	*tmp;

	tmp = job_order;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = n_order;
}

void	ft_create_jobs(t_tree *c)
{
	t_job	*njob;
	t_list	*new_order;

	new_order = ft_lstnew(NULL, 0);
	if (first_job)
	{
		njob = (t_job *)ft_memalloc(sizeof(t_job));
		add_n_job(njob);
		fill_for_jobs(njob, c);
		new_order->content = njob;
		add_n_order(new_order);
	}
	else
	{
		first_job = (t_job *)ft_memalloc(sizeof(t_job));
		first_job->num = 1;
		fill_for_jobs(first_job, c);
		new_order->content = first_job;
		job_order = new_order;
	}
	ft_printf("\nfill for jobs ligne 236 : apel de l execution du job control\n");
	check_run_v2(c);
}

t_tree	*check_run(t_tree *c)
{
	t_tree *tmp;

	tmp = c;
	while (tmp->right)
		tmp = tmp->right;
	if (tmp->token.id == AND)
	{
		ft_create_jobs(c);
		return (c->left);
	}
	return (check_run_v2(c));
}

int		ft_fill_for_jobs(t_tree *head)
{
	t_tree		*tmp;

	tmp = head;
	init_closefd(closefd);
	while (tmp)
		tmp = check_run(tmp);
	if (job_order)
		ft_free_order(job_order);
	return (ft_free_tree(head));
}
