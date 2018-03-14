/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_job.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:32:43 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/14 20:53:34 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	wait_for_job(t_job *j)
{
	int		status;
	pid_t	pid;

	while (1)
	{
		// pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		pid = waitpid(WAIT_ANY, &status, 0);
		DEBUG("pid find : %d\n", pid);
		if (mark_process_status(pid, status) || job_is_running(j) == 0)
			break ;
	}
	DEBUG("job_is_running : %d\n", job_is_running(j));
}
