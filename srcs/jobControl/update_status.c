/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:32:11 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/16 22:33:05 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

// void	update_status(void)
// {
// 	t_job	*tmp;
// 	int		status;

// 	tmp = g_first_job;
// 	while (tmp)
// 	{
// 		status = 0;
// 		if (waitpid(tmp->pgid, &status, WUNTRACED | WNOHANG | WCONTINUED) > 0)
// 			mark_process_status(tmp->pgid, status);
// 		tmp = tmp->next;
// 	}
// }

void	update_status(void)
{
	pid_t	pid;
	int		status;

	while (1)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
		if (pid < 0 || mark_process_status(pid, status) == 1)
			break ;
	}
}

// void
// update_status (void)
// {
//   int status;
//   pid_t pid;

//   do
//     pid = waitpid (WAIT_ANY, &status, WUNTRACED|WNOHANG);
//   while (!mark_process_status (pid, status));
// }
