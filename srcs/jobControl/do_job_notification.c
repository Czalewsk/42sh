/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_job_notification.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:36:06 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/24 12:47:20 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	del_job_in_order(t_job *j)
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
			ft_memdel((void**)&tmp);
			break ;
		}
		else
			last = tmp;
		tmp = next;
	}
}

void	del_job_in_first(t_job *j)
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
			del_job_in_order(j);
			free_job(j);
			break ;
		}
		else
			last_job = tmp;
		tmp = next_job;
	}
}

void	free_job(t_job *j)
{
	ft_memdel((void**)&(j->command));
	if (j->finish_command)
	{
		ft_free_tree(j->finish_command);
		j->finish_command = NULL;
	}
	ft_free_process(j->process);
	ft_memdel((void**)&(j));
}

void	do_job_notification(void)
{
	t_job	*tmp;
	t_job	*next_job;

	update_status();
	tmp = g_first_job;
	while (tmp)
	{
		next_job = tmp->next;
		if (job_is_completed(tmp) == 1)
		{
			jobs_display(tmp, 0, g_sh.fd_tty);
			del_job(tmp);
		}
		else if (job_is_stopped(tmp) == 1 && !tmp->notified)
		{
			jobs_display(tmp, 0, g_sh.fd_tty);
			tmp->notified = 1;
		}
		tmp = next_job;
	}
	clear_completed_job();
}
