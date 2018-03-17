/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_process_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:31:22 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/17 19:29:58 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int	mark_process(t_job *j, pid_t pid, int status)
{
	t_process	*p;

	p = j->process;
	while (p)
	{
		if (p->pid == pid)
		{
			p->status = status;
			if (p->next == NULL)
				j->status_last_process = status;
			if (WIFSTOPPED(status))
			{
				p->state = PROCESS_STOPPED;
				j->notified = 0;
			}
			else if (WIFCONTINUED(status))
				p->state = PROCESS_RUNNING;
			else
				p->state = PROCESS_COMPLETED;
			put_first_in_job_order(j);
			return (0);
		}
		p = p->next;
	}
	return (1);
}

int	mark_process_status(pid_t pid, int status)
{
	t_job	*tmp;

	if (pid == 0)
		return (1);
	else if (pid < 0)
		return (sh_error(0, 0, NULL, 1, "job control: waitpid"));
	tmp = g_first_job;
	while (tmp)
	{
		if (mark_process(tmp, pid, status) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
