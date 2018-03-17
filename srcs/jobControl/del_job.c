/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_job.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 17:27:11 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/17 16:54:50 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_list	*pop_job_from_job_order(t_job *j)
{
	t_list	*tmp;
	t_list	*last;
	t_list	*next;

	tmp = g_job_order;
	last = NULL;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->content == j)
		{
			if (last)
				last->next = next;
			else
				g_job_order = next;
			return (tmp);
		}
		else
			last = tmp;
		tmp = next;
	}
	return (NULL);
}

void	pop_job_from_first_job(t_job *j)
{
	t_job	*tmp;
	t_job	*last_job;
	t_job	*next_job;

	tmp = g_first_job;
	last_job = NULL;
	while (tmp)
	{
		next_job = tmp->next;
		if (j == tmp)
		{
			if (last_job)
				last_job->next = next_job;
			else
				g_first_job = next_job;
			break ;
		}
		else
			last_job = tmp;
		tmp = next_job;
	}
}

void	del_job(t_job *j)
{
	t_list	*res;

	res = pop_job_from_job_order(j);
	if (res)
		ft_memdel((void**)&res);
	pop_job_from_first_job(j);
	free_job(j);
}

void	clear_completed_job(void)
{
	t_job	*tmp;
	t_job	*next;

	tmp = g_first_job;
	while (tmp)
	{
		next = tmp->next;
		if (job_is_completed(tmp) == 1)
			del_job(tmp);
		tmp = next;
	}
}

void	clear_job(void)
{
	t_job	*tmp;
	t_job	*next;

	tmp = g_first_job;
	while (tmp)
	{
		next = tmp->next;
		del_job(tmp);
		tmp = next;
	}
}
