/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_is_stopped.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 13:35:32 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/04 12:54:52 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int	job_is_stopped(t_job *j)
{
	t_process	*p;

	p = j->process;
	DEBUG("\n\njob_is_stopped ligne 20 : complet : %d ---- stopped : %d\n", p->completed, p->stopped);
	if (p->completed != 0 && p->stopped != 0)
		return (0);
	// while (p != NULL)
	// {
	// 	if (p->completed != 0 && p->stopped != 0)
	// 		return (0);
	// }
	return (1);
}
