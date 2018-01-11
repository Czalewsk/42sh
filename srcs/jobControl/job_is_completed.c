/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_is_completed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 13:40:18 by scorbion          #+#    #+#             */
/*   Updated: 2017/12/03 13:42:16 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/job_control.h"

int	job_is_completed(t_job *j)
{
	t_process *p;

	p = j->first_process;
	while (p != NULL)
	{
		if (p->completed != 0)
			return (0);
	}
	return (1);
}
