/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_is_completed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 13:40:18 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/03 16:26:25 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int	job_is_completed(t_job *j)
{
	t_process *p;

	p = j->process;
	if (p->completed != 0)
		return (0);
	// while (p != NULL)
	// {
	// 	if (p->completed != 0)
	// 		return (0);
	// }
	return (1);
}
