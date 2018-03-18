/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 09:55:58 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/18 18:30:51 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int	job_is_stopped(t_job *j)
{
	t_process	*p;

	p = j->process;
	while (p != NULL)
	{
		if (p->state != PROCESS_STOPPED && p->state != PROCESS_COMPLETED)
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
		if (p->state == PROCESS_RUNNING)
			return (1);
		p = p->next;
	}
	return (0);
}
