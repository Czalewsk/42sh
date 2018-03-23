/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_foreground.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:28:13 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/20 14:13:40 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void	pop_job_from_list(t_job *j)
{
	t_list	*res;

	res = pop_job_from_job_order(j);
	if (res)
		ft_memdel((void**)&res);
	pop_job_from_first_job(j);
}

void		display_process_interrupt(t_job *job)
{
	ft_putstr_fd("\n[", g_sh.fd_tty);
	ft_putnbr_fd(job->num, g_sh.fd_tty);
	ft_putstr_fd("]", g_sh.fd_tty);
	if (g_job_order)
	{
		if ((t_job*)(g_job_order->content) == job)
			ft_putstr_fd("+", g_sh.fd_tty);
		else if (g_job_order->next &&
			(t_job*)(g_job_order->next->content) == job)
			ft_putstr_fd("-", g_sh.fd_tty);
		else
			ft_putstr_fd(" ", g_sh.fd_tty);
	}
	ft_putstr_fd(" Stopped		", g_sh.fd_tty);
	ft_putendl_fd(job->command, g_sh.fd_tty);
	job->notified = 1;
}

t_job		*get_next_job(t_job *j)
{
	t_job	*next;

	if (!(next = NULL) && job_is_completed(j))
		pop_job_from_list(j);
	else
		display_process_interrupt(j);
	if (WIFSIGNALED(j->status_last_process))
	{
		if (WTERMSIG(j->status_last_process) == SIGINT)
			write(g_sh.fd_tty, "\n", 1);
		else
			process_display_short(j->process, j->command, g_sh.fd_tty);
	}
	else
		next = get_new_job(j->finish_command, WIFEXITED(j->status_last_process)
			? WEXITSTATUS(j->status_last_process) : 1, j->foreground);
	ft_free_tree(j->finish_command);
	j->finish_command = NULL;
	if (job_is_completed(j))
	{
		g_sh.exitstatus = WIFEXITED(j->status_last_process)
			? WEXITSTATUS(j->status_last_process) : 1;
		free_job(j);
	}
	return (next);
}

t_job		*put_job_in_foreground(t_job *j, int cont)
{
	t_job	*next;

	tcsetpgrp(g_shell_terminal, j->pgid);
	if (cont)
	{
		tcsetattr(g_shell_terminal, TCSADRAIN, &j->tmodes);
		if (kill(-j->pgid, SIGCONT) < 0)
			sh_error(1, 0, NULL, 1, "job control: kill SIGCONT");
	}
	wait_for_job(j);
	tcsetpgrp(g_shell_terminal, g_shell_pgid);
	tcgetattr(g_shell_terminal, &j->tmodes);
	termcaps_set_tty();
	next = get_next_job(j);
	return (next);
}
