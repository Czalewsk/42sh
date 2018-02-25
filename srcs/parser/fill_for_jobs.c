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

extern  t_check_proc g_check_procs[];

t_tree			*check_run_v2(t_tree *c)
{
	t_tree		*tmp;
	t_tree		*stop;

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
			g_sh.exitstatus = execute_run(tmp, stop->right, NULL);
		stop ? stop = stop->right : stop;
	}
	return (c->left);
}

t_tree			*check_run(t_tree *c)
{
	t_tree		*tmp;

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

int				ft_fill_for_jobs(t_tree *head)
{
	t_tree		*tmp;

	tmp = head;
	init_closefd(g_sh.fds);
	while (tmp)
		tmp = check_run(tmp);
	if (job_order)
		ft_free_order(job_order);
	return (ft_free_tree(head));
}
