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
			if (tmp && tmp->token.id == AND_IF && current_process->returned != 0)
			{
				if ((tmp = get_new_from_failure_and(tmp)) == NULL)
					return (tmp);
			}
			else if (tmp->token.id == OR_IF && current_process->returned == 0)
				tmp = new_success_or_if(tmp);
			else
				tmp = tmp->right;
		}
		if (tmp)
			init_current_process();
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
			c = g_cmd_actions[i].fjob(current_process, c);
			if (c == (void *)1)
				return ((void *)1);
			i = -1;
		}
	}
	set_fd(current_process);
	if (check_built_in(current_process) == 0)
		do_built_in(current_process);
	else
		execute(current_process, job, env_make(ENV_GLOBAL | ENV_TEMP), 1);
	reset_fdd(current_process);
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
	// else
	// 	return (ft_create_jobs(c));
	return (split_and_if_pipe(c, NULL));
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
	if (here_list)
		ft_lstdel(&here_list, NULL);
	return (ft_free_tree(head));
}
