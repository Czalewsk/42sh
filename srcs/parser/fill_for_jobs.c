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

t_tree	*fill_io(t_tree *clist, t_job *job)
{
	(void)job;
	return (clist);
}

t_job	*fill_job_process(t_tree *list, t_job *job)
{
	int		i;

	i = 0;
	while (g_fill_jobs[i].fjob)
	{
		if (g_fill_jobs[i].one == list->token.id)
		{
			list = g_fill_jobs[i].fjob(list, job);
			if (list)
				return (job = fill_job_process(list, job));
			return (job);
		}
		i++;
	}
	ft_printf("who came here > ?");
	return (NULL);
}

t_job	*fill_job(t_job *fill, t_tree *chead)
{
	t_job	*new;
	t_process *fp;
	t_tree	*tmp;

	new = NULL;
	tmp = chead;
	fill = init_job(fill);
	fp = fill->first_process;
	fill = fill_job_process(tmp, init_job(fill));
	fill->first_process = fp;
	fill->next = new;
	return (new);
}

int		ft_fill_for_jobs(t_tree *head)
{
	t_job	*first_job;
	t_job	*n;
	t_tree	*tmp;

	tmp = head;
	first_job = NULL;
	n = first_job;
	while (tmp)
	{
		n = fill_job(n, tmp);
		tmp = tmp->left;
	}
	return (0);
}