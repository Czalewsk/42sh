/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:32:11 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/10 14:08:38 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	update_status(void)
{
	t_job	*tmp;
	int		status;

	tmp = first_job;
	while (tmp)
	{
		status = 0;
		if (waitpid(tmp->pgid, &status, WUNTRACED | WNOHANG) > 0)
			mark_process_status(tmp->pgid, status);
		tmp = tmp->next;
	}
}
