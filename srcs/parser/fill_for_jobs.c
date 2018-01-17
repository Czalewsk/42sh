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

void	ft_affiche_procces(t_process *p)// tmp
{
	int	i;

	while (p)
	{
		i = 0;
		while (p->argv && p->argv[i])
			ft_printf("\n%s\n", p->argv[i++]);
		p = p->next;
		if (p)
			ft_printf("\n PIPED TO\n");
	}
}

void	ft_affiche_jobs(t_job *fjob)// tmp
{
	ft_printf("\nFirst Job\n");
	while (fjob)
	{
		ft_affiche_procces(fjob->first_process);
		fjob = fjob->next;
		if (fjob)
			ft_printf("\nNew Job\n");
	}
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
	i = 0;
	ft_printf("\nWrong to come here, but for test it is ok\n");
	list = g_fill_jobs[i].fjob(list, job);
	if (list)
		return (job = fill_job_process(list, job));
			free(job->first_process->next);
	return (job);
}

t_job	*fill_job(t_job *job, t_tree *chead)
{
	t_process	*fp;
	t_tree		*tmp;

	fp = NULL;
	tmp = chead;
	job->first_process = init_process(job->first_process);
	fp = job->first_process;
	job = fill_job_process(tmp, job);
	job->first_process = fp;
	return (job);
}

int		ft_fill_for_jobs(t_tree *head)
{
	t_job	*first_job;
	t_job	*n;
	t_tree	*tmp;

	tmp = head;
	first_job = NULL;
	n = NULL;
	n = init_job(n);
	while (tmp)
	{
		if (first_job == NULL)
			first_job = n;
		n = fill_job(n, tmp);
		tmp = tmp->left;
		if (tmp)
		{
			n->next = init_job(n->next);
			n = n->next;
		}
	}
	n = first_job;
	ft_affiche_jobs(first_job);
	ft_printf("\nReady to launch\n");
	ft_free_job(n);
	ft_printf("\nJob freed\n");
	return (0);
}