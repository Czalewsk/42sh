/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_job.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 17:27:11 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/09 18:34:20 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

// t_list		*pop_job_from_job_order(t_job *j)
// {
// 	t_list  *tmp;
// 	t_list  *target;
	
// 	tmp = job_order;
// 	if ((t_job*)tmp->content == j)
// 	{
// 		target = &(*tmp);
// 		job_order = tmp->next;
// 		return (target);
// 	}
// 	while (tmp->next && (t_job*)tmp->next->content != j)
// 		tmp = tmp->next;
// 	if (tmp->next == NULL)
// 	{
// 		sh_error(1, 0, NULL, 1, "job not found in job order");
// 		return (NULL);
// 	}
// 	target = tmp->next;
// 	tmp->next = tmp->next->next;
// 	return (target);
// }

t_list		*pop_job_from_job_order(t_job *j)
{
	t_list	*tmp;
	t_list	*last;
	t_list	*next;

	tmp = job_order;
	last = NULL;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->content == j)
		{
			if (last)
				last->next = next;
			else
				job_order = next;
			return (tmp);
		}
		else
			last = tmp;
		tmp = next;
	}
	return (NULL);
}

void		pop_job_from_first_job(t_job *j)
{
	t_job	*tmp;
	t_job	*last_job;
	t_job	*next_job;

	tmp = first_job;
	last_job = NULL;
	while (tmp)
	{
		next_job = tmp->next;
		if (j == tmp)
		{
			if (last_job)
				last_job->next = next_job;
			else
				first_job = next_job;
			break ;
		}
		else
			last_job = tmp;
		tmp = next_job;
	}
}

void		free_job2(t_job *j)
{
	ft_memdel((void**)&(j->command));
	ft_free_process(j->process);
	ft_memdel((void**)&(j));
}

void		del_job(t_job *j)
{
	t_list	*res;

	res = pop_job_from_job_order(j);
	if (res)
		ft_memdel((void**)&res);
	pop_job_from_first_job(j);
	free_job2(j);
}

void		clear_completed_job()
{
	t_job	*tmp;
	t_job	*next;

	tmp = first_job;
	while (tmp)
	{
		next = tmp->next;
		if (job_is_completed(tmp) == 0)
		{
			del_job(tmp);
		}
		tmp = next;
	}
}
