/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_process_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:31:22 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/08 10:12:21 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"   

int mark_process_status (pid_t pid, int status)
{
	t_job		*tmp;
	t_process	*p;
	
	if (pid == 0)
		return -1;
	else if (pid < 0)
		return (sh_error(1, 0, NULL, 1, "job control: waitpid"));
	tmp = first_job;
	while (tmp)
	{
		p = tmp->process;
		if (p->pid == pid)
		{
			p->status = status;
			if (WIFSTOPPED (status))
			{
				DEBUG("mark_process_status ligne 75 : process %d est stop\n", p->pid);
				p->stopped = 1;
			}
			else
			{
				DEBUG("mark_process_status ligne 80 : process %d est fini\n", p->pid);
				p->completed = 1;
				/*
				if (WIFSIGNALED (status))
				fprintf (stderr, "%d: Terminated by signal %d.\n",
							(int) pid, WTERMSIG (p->status));
				*/
			}
			return 0;
		}
		tmp = tmp->next;
	}
	return -1;
}