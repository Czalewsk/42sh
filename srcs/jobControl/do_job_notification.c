/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_job_notification.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:36:06 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/16 22:16:03 by scorbion         ###   ########.fr       */
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
	DEBUG("START FREE JOB\n");
	ft_memdel((void**)&(j->command));
	ft_free_process(j->process);
	ft_memdel((void**)&(j));
	DEBUG("FIN FREE JOB\n");
}

void	do_job_notification(void)
{
	t_job	*tmp;
	t_job	*last_job;
	t_job	*next_job;
	t_job	*tmp2;
	t_job	*trash;
	t_list	*res;

	update_status();
	tmp = g_first_job;
	last_job = NULL;
	while (tmp)
	{
		next_job = tmp->next;
		if (tmp->foreground == 0)
		{
			if (job_is_completed(tmp) == 1)// && next_on_tree(tmp->finish_command, tmp->status_last_process) == NULL)
				jobs_display(tmp, 0);
			else if (job_is_stopped(tmp) == 1 && !tmp->notified)
			{
				jobs_display(tmp, 0);
				tmp->notified = 1;
			}
		}
		tmp = next_job;
	}
	
	DEBUG("AVANT boucle qui relance les jobs\n");
	tmp = g_first_job;
	while (tmp)
	{
		if (job_is_running(tmp) == 0 && job_is_stopped(tmp) == 0)
		{
			if (job_is_completed(tmp))
			{
				DEBUG("job cmd : %s\n", tmp->command)
				res = pop_job_from_job_order(tmp);
				if (res)
					ft_memdel((void**)&res);
				pop_job_from_first_job(tmp);
			}
			else
				DEBUG("job PAS COMPLET\n")
			//print_job_order();
			tmp2 = get_new_job(tmp->finish_command, tmp->status_last_process, tmp->foreground);
			//DEBUG("ft_fill_for_jobs : BESOIN DE FREE sur la ligne ref->finish_command = NULL;\n")
			tmp->finish_command = NULL;
			trash = tmp;
			tmp = tmp->next;
			// if (job_is_completed(trash))
			// {
			// 	DEBUG("cmd trash : %s\n", trash->command);
			// 	//del_job(trash);

			// }
			if (!tmp2)
				DEBUG("tmp2  null\n")
			else
				execute_job(tmp2);
		}
		else
			tmp = tmp->next;
	}
	DEBUG("APRES boucle qui relance les jobs\n");
	clear_completed_job();
}
