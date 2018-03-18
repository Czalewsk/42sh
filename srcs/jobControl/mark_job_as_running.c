/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mark_job_as_running.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:40:00 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/18 16:16:18 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	mark_job_as_running(t_job *j)
{
	t_process *p;

	p = j->process;
	while (p)
	{
		if (p->state != PROCESS_COMPLETED)
			p->state = PROCESS_RUNNING;
		p = p->next;
	}
	j->notified = 0;
}
