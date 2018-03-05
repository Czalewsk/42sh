/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_is_stopped.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 13:35:32 by scorbion          #+#    #+#             */
/*   Updated: 2017/12/03 13:42:29 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/job_control.h"

int	job_is_stopped(t_job *j)
{
	t_process	*p;

	p = j->first_process;
	while (p != NULL)
	{
		if (p->completed != 0 && p->stopped != 0)
			return (0);
	}
	return (1);
}
