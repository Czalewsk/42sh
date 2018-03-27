/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_job_in_background.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:29:53 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/24 10:46:35 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	put_job_in_background(t_job *j, int cont)
{
	char	*num;
	char	*pid;
	char	*print;

	if (j->status_last_process == 0)
	{
		num = ft_itoa(j->num);
		pid = ft_itoa(j->process->pid);
		print = ft_strxjoin(4, "[", num, "] ", pid);
		ft_putendl_fd(print, g_sh.fd_tty);
		ft_memdel((void**)&num);
		ft_memdel((void**)&pid);
		ft_memdel((void**)&print);
	}
	g_sh.exitstatus = 0;
	if (cont)
		if (kill(-j->pgid, SIGCONT) < 0)
			sh_error(1, 0, NULL, 1, "job control: kill SIGCONT");
}
