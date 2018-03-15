/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 09:55:58 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/15 10:39:45 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int	job_is_stopped(t_job *j)
{
	t_process	*p;

	p = j->process;
	while (p != NULL)
	{
		if (p->state != PROCESS_STOPPED)
			return (0);
		p = p->next;
	}
	return (1);
}

int	job_is_completed(t_job *j)
{
	t_process	*p;

	p = j->process;
	while (p != NULL)
	{
		DEBUG("status process pid : %d --- %d\n", p->pid, p->state);
		if (p->state != PROCESS_COMPLETED)
			return (0);
		p = p->next;
	}
	return (1);
}

int	job_is_running(t_job *j)
{
	t_process	*p;

	p = j->process;
	while (p != NULL)
	{
		if (p->state == PROCESS_STOPPED || p->state == PROCESS_COMPLETED)
			return (0);
		p = p->next;
	}
	return (1);
}
