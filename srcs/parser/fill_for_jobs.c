/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_for_jobs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 17:31:28 by maastie           #+#    #+#             */
/*   Updated: 2018/03/13 17:50:14 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

extern	t_cmd_action	g_cmd_actions[];

t_tree				*check_and_do_pipe(t_tree *c, t_job *job)
{
	t_tree			*tmp;
	t_tree			*ret;

	tmp = c;
	while (tmp)
	{
		if (tmp->token.id == AND_IF || tmp->token.id == OR_IF)
			return (c);
		else if (tmp->token.id == PIPE)
		{
			while (tmp && tmp->right && (tmp->token.id != AND_IF && tmp->token.id != OR_IF))
				tmp = tmp->right;
			ret = tmp;
			while (tmp && tmp->previous && tmp->previous->token.id != PIPE)
				tmp = tmp->previous;
			termcaps_restore_tty();
			do_pipe(c, tmp, job);
			termcaps_set_tty();
			!ret->right ? ret = ret->right : 0;
			return (ret);
		}
		tmp = tmp->right;
	}
	return (c);
}

t_tree 			*init_new_job(t_tree *c)
{
	t_job 		*job;
	t_list		*new_order;
	t_tree		*tmp;

	tmp = c;
	job = (t_job *)ft_memalloc(sizeof(t_job));
	new_order = ft_lstnew(NULL, 0);
	new_order->content = job;
	job->command = get_command(job->command, c);
	job->num = get_id_max_job();
	// A MODIFIRE POUR L ORDRE DES JOB TEST IS FOR FREE
	new_order->next = g_job_order;
	g_job_order = new_order;
	job->foreground = 0;
	job->process = (t_process *)ft_memalloc(sizeof(t_process));
	job->free_process = job->process;
	job->process->stdout = 1;
	job->process->stderr = 2;
	while (tmp->right)
		tmp = tmp->right;
	if (tmp->token.id == AND)
	{
		if (g_sh.subshellactive == 1)
			tmp->token.id = SEMI;
		else
			job->foreground = 1;
	}
	return (execute_run(c, job));
}

t_tree				*execute_run(t_tree *c, t_job *job)
{
	t_tree			*tmp;

	tmp = c;
	while (tmp)
	{
		tmp = check_and_do_pipe(tmp, job);
		if (tmp && (tmp->token.id != AND_IF && tmp->token.id != OR_IF))
			if ((tmp = cmd_action(tmp, job)) == ((void *)1))
				return (tmp);
		if (tmp)
		{
			if (tmp && tmp->token.id == AND_IF && job->process->status != 0)
			{
				if ((tmp = get_new_from_failure_and(tmp)) == NULL)
					return (tmp);
			}
			else if (tmp->token.id == OR_IF && job->process->status == 0)
				tmp = new_success_or_if(tmp);
			else
				tmp = tmp->right;
		}
		if (tmp)
			return (init_new_job(tmp));
	}
	return (c);
}

t_tree			*cmd_action(t_tree *c, t_job *job)
{
	int			i;
	t_tree		*tmp;

	tmp = c;
	i = -1;
	while (c && g_cmd_actions[++i].fjob)
	{
		if (c && (c->token.id == OR_IF || c->token.id == AND_IF))
			break ;
		if (c && g_cmd_actions[i].one == c->token.id)
		{
			c = g_cmd_actions[i].fjob(job->process, c);
			if (c == (void *)1)
				return ((void *)1);
			i = -1;
		}
	}
	job->finish_command = c;
	set_fd(job->process);
	if (do_built_in(job->process, env_make(ENV_GLOBAL | ENV_TEMP)) == 0)
		execute(job, env_make(ENV_GLOBAL | ENV_TEMP), 1); // virer le t_process vue au on a le job
	reset_fdd(job->process);
	return (c);
}

t_tree 			*split_and_if_pipe(t_tree *c, t_job *job)
{
	t_tree 		*tmp;

	tmp = c;
	job->process = (t_process *)ft_memalloc(sizeof(t_process));
	job->process->stdout = 1;
	job->process->stderr = 2;
	job->free_process = job->process;
	tmp = execute_run(tmp, job);
	if (tmp == (void *)1)
		return (NULL);
	return (tmp);
}

t_tree			*split_cmd_jobs(t_tree *c)
{
	t_job 		*job;
	t_list		*new_order;
	t_tree		*tmp;

	tmp = c;
	job = (t_job *)ft_memalloc(sizeof(t_job));
	new_order = ft_lstnew(NULL, 0);
	new_order->content = job;
	job->command = get_command(job->command, c);
	job->num = get_id_max_job();
	g_job_order ? (new_order->next = g_job_order) : (g_job_order = new_order);
	job->foreground = 0;
	while (tmp->right)
		tmp = tmp->right;
	if (tmp->token.id == AND)
	{
		if (g_sh.subshellactive == 1)
			tmp->token.id = SEMI;
		else
			job->foreground = 1;
	}
	return (split_and_if_pipe(c, job));
}

int				ft_fill_for_jobs(t_tree *head)
{
	t_tree		*tmp;

	tmp = head;
	while (tmp)
	{
		if ((split_cmd_jobs(tmp)) == (void *)1)
			break ;
		tmp = tmp->left;
	}
	ft_free_order(g_job_order);
	return (ft_free_tree(head));
}
