/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_job.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 13:17:43 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/11 11:28:32 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_job	*find_job(pid_t pgid)
{
	t_job	*tmp;

	tmp = g_first_job;
	while (tmp)
	{
		if (tmp->pgid == pgid)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
