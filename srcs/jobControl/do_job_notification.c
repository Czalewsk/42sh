/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_job_notification.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:36:06 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/15 10:37:49 by scorbion         ###   ########.fr       */
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
	ft_free_process(j->process);
	ft_memdel((void**)&(j));
}

void	do_job_notification(void)
{
	t_job	*tmp;
	t_job	*last_job;
	t_job	*next_job;
	t_tree	*tmp2;

	update_status();
	tmp = g_first_job;
	last_job = NULL;
	while (tmp)
	{
		next_job = tmp->next;
		if (job_is_completed(tmp) == 1)
			jobs_display(tmp, 0);
		else if (job_is_stopped(tmp) == 1 && !tmp->notified)
		{
			jobs_display(tmp, 0);
			tmp->notified = 1;
		}
		tmp = next_job;
	}

	// DEBUG("AVANT boucle qui relance les jobs\n");
	tmp = g_first_job;
	while (tmp)
	{
		DEBUG("Val status process : %d\n", tmp->process->status)
		if (job_is_running(tmp) == 0 && tmp->notified == 0)
		{
			DEBUG("JOB IS NOT RUNNING\n");
			tmp2 = tmp->finish_command;
			if (tmp2)
			{
				if (tmp2->token.id == AND_IF && tmp->process->status != 0)
				{
					DEBUG("TOKEM IS AN AND\n");
					tmp2 = get_new_from_failure_and(tmp2);
				}
				else if (tmp2->token.id == OR_IF && tmp->process->status == 0)
				{
					// DEBUG("TOKEM IS AN OR\n");
					tmp2 = new_success_or_if(tmp2);
				}
				else
					tmp2 = tmp2->right;
				// DEBUG("TMP2 ID : %d\n", tmp2->token.id);
				// DEBUG("AVANT SPLIT CMD JOB\n");
				//split_cmd_jobs(tmp2, tmp->foreground);
			}
		}
		tmp = tmp->next;
	}
	// DEBUG("APRES boucle qui relance les jobs\n");
	clear_completed_job();
}
