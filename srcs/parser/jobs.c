/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:49:17 by maastie           #+#    #+#             */
/*   Updated: 2018/02/24 20:49:18 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void		add_n_job(t_job *new)
{
	t_job 	*tmp;

	tmp = first_job;
	while (tmp->next)
		tmp = tmp->next;
	new->num = tmp->num + 1;
	tmp->next = new;
}

void		ft_add_jobs()// current_execute;
{
	t_job 	*njob;
	t_list	*new_order;	

	new_order = ft_lstnew(NULL, 0);
	if (first_job)
	{
		njob = (t_job *)ft_memalloc(sizeof(t_job));
		add_n_job(njob);
		njob->process = current_execute;
		new_order->content = njob;
		new_order->next = job_order;
		job_order = new_order;
	}
	else
	{
		first_job = (t_job *)ft_memalloc(sizeof(t_job));
		first_job->num = 1;
		first_job->process = current_execute;
		new_order->content = first_job;
		job_order = new_order;
	}
}

void		ft_create_jobs(t_tree *c)
{
	t_job	*njob;
	t_list	*new_order;

	ft_printf("?\n");
	new_order = ft_lstnew(NULL, 0);
	if (first_job)
	{
		njob = (t_job *)ft_memalloc(sizeof(t_job));
		add_n_job(njob);
		njob->command = get_command(njob->command, c);
		njob->num = job->order->content->num + 1;
		new_order->content = njob;
		new_order->next = job_order;
		job_order = new_order;
	}
	else
	{
		first_job = (t_job *)ft_memalloc(sizeof(t_job));
		first_job->num = 1;
		first_job->command = get_command(first_job->command, c);
		new_order->content = first_job;
		job_order = new_order;
	}
	check_run_v2(c);
}