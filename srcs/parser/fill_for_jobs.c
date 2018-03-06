/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_for_jobs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 17:31:28 by maastie           #+#    #+#             */
/*   Updated: 2018/03/03 19:30:10 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

// ajouter le t_list dans le pipe
// et dans g_checkproc

extern	t_check_proc g_check_procs[];

t_tree			*check_run_v2(t_tree *c, t_job *job)
{
	t_tree		*tp;
	t_tree		*sp;

	tp = c;
	sp = c;
	while (sp)
	{
		if (sp->token.id == AND_IF || sp->token.id == OR_IF
			|| sp->token.id == PIPE)
		{
			sp->token.id == AND_IF ? tp = g_check_procs[0].cproc(tp, sp, job) : tp;
			sp->token.id == OR_IF ? tp = g_check_procs[1].cproc(tp, sp, job) : tp;
			sp->token.id == PIPE ? tp = g_check_procs[2].cproc(tp, sp, job) : tp;
			if (tp == (void *)1)
				return (NULL);
			sp = tp;
		}
		if (sp && sp->right == NULL)
			g_sh.exitstatus = execute_run(tp, sp->right, job);
		sp ? sp = sp->right : sp;
	}
	return (c->left);
}

t_tree			*check_run(t_tree *c)
{
	t_tree		*tmp;

	tmp = c;
	while (tmp->right)
	{
		DEBUG("str=%s|\n", tmp->right->token.str);
		tmp = tmp->right;
	}
	if (tmp->token.id == AND)
	{
		DEBUG("check run\n");
		ft_create_jobs(c);
		return (c->left);
	}
	return (check_run_v2(c, NULL));
}

int				ft_fill_for_jobs(t_tree *head)
{
	t_tree		*tmp;

	tmp = head;
	init_closefd(g_sh.fds);
	while (tmp)
		tmp = check_run(tmp);
	if (job_order)
	{
//		ft_printf("fill_for_jobs l:68 si tu veux pas free la list de job\n");
//		job_order = job_order->next;
//		ft_free_order(job_order);
	}
	return (ft_free_tree(head));
}
