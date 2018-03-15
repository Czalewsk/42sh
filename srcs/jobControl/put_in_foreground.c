/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_foreground.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:28:13 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/15 09:51:44 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	display_process_interrupt(t_job *job)
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

void	put_job_in_foreground(t_job *j, int cont)
{
	t_tree	*tmp;
	int		job_ret;
	
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
	DEBUG("PGID ayant le shell : %d ----- PGID du shell %d ----- PGID du job %d\n", tcgetpgrp(g_shell_terminal), g_shell_pgid, j->pgid);
	if (WIFSTOPPED(j->process->status))
	{
		display_process_interrupt(j);
		tmp = j->finish_command;
		if (tmp)
		{
			if (tmp->token.id == AND_IF && j->process->status != 0)
				tmp = get_new_from_failure_and(tmp);
			else if (tmp->token.id == OR_IF && j->process->status == 0)
				tmp = new_success_or_if(tmp);
			else
				tmp = tmp->right;
			if (tmp)
				DEBUG("token : %s\n", tmp->token.str);
			split_cmd_jobs(tmp, j->foreground);
		}
	}
	// if (WIFSIGNALED(j->process->status))
	// {
	// 	WTERMSIG(j->process->status);
	// 		ft_putstr_fd("Killed : 2", g_sh.fd_tty);
	// 	ft_putendl_fd("", g_sh.fd_tty);
	// }
	

	// DEBUG("ret job complet : %d\n", job_is_completed(j));
	if (job_is_completed(j))
	{
		// DEBUG("cmd %s, val retour %d\n", j->command, j->process->status);
		tmp = j->finish_command;
		job_ret = j->process->status;
		del_job(j);
		if (tmp)
		{
			if (tmp->token.id == AND_IF && job_ret != 0)
			{
				tmp = get_new_from_failure_and(tmp);
			}
			else if (tmp->token.id == OR_IF && job_ret == 0)
				tmp = new_success_or_if(tmp);
			else
				tmp = tmp->right;
			split_cmd_jobs(tmp, j->foreground);
		}
	}
}

void	put_process_in_foreground(t_process *p, int cont)
{
	t_job	*newjob;

	tcsetpgrp(g_shell_terminal, p->pid);
	if (cont)
	{
		if (kill(-p->pid, SIGCONT) < 0)
			sh_error(1, 0, NULL, 1, "job control: kill SIGCONT");
	}
	waitpid(p->pid, &g_sh.exitstatus, WUNTRACED);
	p->status = g_sh.exitstatus;
	if (WIFSTOPPED(p->status))
	{
		newjob = ft_create_jobs(NULL);
		newjob->process = cpy_profonde_process(p);
		newjob->process->state = PROCESS_STOPPED;
		newjob->pgid = getpgid(p->pid);
		tcgetattr(g_shell_terminal, &newjob->tmodes);
		termcaps_set_tty();
		display_process_interrupt(newjob);
	}
	tcsetpgrp(g_shell_terminal, g_shell_pgid);
}
