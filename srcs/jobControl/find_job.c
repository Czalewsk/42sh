/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 13:17:43 by scorbion          #+#    #+#             */
/*   Updated: 2017/12/03 13:35:07 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/job_control.h"

t_job	*find_job(pid_t pgid)
{
	t_job	*tmp;

	tmp = first_job;
	while (tmp)
	{
		if (tmp->pgid == pgid)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}