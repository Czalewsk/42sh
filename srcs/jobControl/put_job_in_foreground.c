/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_job_in_foreground.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:28:13 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/10 15:55:17 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	put_job_in_foreground(t_job *j, int cont)
{
	DEBUG("PUT_JOB_IN_FOREGROUND\n");
	DEBUG("Retour du setpgrp pour donner la main sur le terminal au job : %d\n", tcsetpgrp(shell_terminal, j->pgid));
	if (cont)
	{
	// if (j->tmodes != NULL)
	// {
	//   DEBUG("Retour de setattr pour mettre en place les termios du job : %d\n", tcsetattr (shell_terminal, TCSADRAIN, &j->tmodes));
	// }
	// else
	// {
		termcaps_restore_tty();
		DEBUG("j->tmodes est NULL, dans ce cas mise en place des termios du shell de base\n");
	// }
		if (kill(-j->pgid, SIGCONT) < 0)
			sh_error(1, 0, NULL, 1, "job control: kill SIGCONT");
	}
	DEBUG("Fin du IF cont, debut de wait for job\n");
	wait_for_job(j);
	DEBUG("wait for job termine\n");
	DEBUG("Retour de setpgrp pour donner la main sur le terminal au shell : %d\n", tcsetpgrp(shell_terminal, shell_pgid));
	DEBUG("Retour de getattr pour prendre les termios du job : %d\n", tcgetattr(shell_terminal, &j->tmodes));
	termcaps_set_tty();
	DEBUG("put job in foreground est fini");
	if (job_is_completed(j))
		del_job(j);
}

void	put_job_in_foregroundv2(t_process *p, int cont)
{
	tcsetpgrp(shell_terminal, p->pid);
	if (cont)
	{
		if (kill(-p->pid, SIGCONT) < 0)
			sh_error(1, 0, NULL, 1, "job control: kill SIGCONT");
	}
	waitpid(p->pid, &g_sh.exitstatus, WUNTRACED);
	tcsetpgrp(shell_terminal, shell_pgid);
}
