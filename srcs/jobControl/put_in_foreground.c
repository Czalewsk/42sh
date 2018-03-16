/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_foreground.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:28:13 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/16 21:23:30 by scorbion         ###   ########.fr       */
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
	if (WIFSTOPPED(j->status_last_process))
	{

		display_process_interrupt(j);
		// DEBUG("j->status_last_process = %d\n", WEXITSTATUS(j->status_last_process));
		// if (j->finish_command)
		// 	DEBUG("\n\n\n\n\n\n\n j->finish_command : %s\n\n\n\n\n\n\n", j->finish_command->token.str)
		// next = get_new_job(j->finish_command, j->status_last_process, j->foreground);
		// if (j->finish_command)
		// 	DEBUG("\n\n\n\n\n\n\n j->finish_command : %s\n\n\n\n\n\n\n", j->finish_command->token.str)
		// tmp = j->finish_command;
		// j->finish_command = NULL;
		// if (tmp)
		// {

		// 	if (tmp->token.id == AND_IF && j->process->status != 0)
		// 		tmp = get_new_from_failure_and(tmp);
		// 	else if (tmp->token.id == OR_IF && j->process->status == 0)
		// 		tmp = new_success_or_if(tmp);
		// 	else
		// 		tmp = tmp->right;
		// 	if (tmp)
		// 		DEBUG("token : %s\n", tmp->token.str);
		// 	split_cmd_jobs(tmp, j->foreground);
		// }
		//return (next);
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
		DEBUG("WEXITSTATUS(j->status_last_process) : %d\n", WEXITSTATUS(j->status_last_process))
		next = get_new_job(j->finish_command, WEXITSTATUS(j->status_last_process), j->foreground);
		DEBUG("toto\n");
		print_job(next);
		
		execute_job(next);
		sleep(5);
		// DEBUG("cmd %s, val retour %d\n", j->command, j->process->status);
		// tmp = j->finish_command;

		// j->finish_command = NULL;
		// job_ret = j->process->status;
		//get_new_job(tmp2->finish_command, tmp2->status_last_process, tmp2->foreground);
		del_job(j);
		// DEBUG("Job is complete if %s\n", tmp->token.str);
		// if (tmp)
		// {
		// 	DEBUG("job_ret = %d || IF TMP  == %s\n", job_ret, tmp->token.str);
		// 	if (tmp->token.id == AND_IF && job_ret != 0)
		// 	{
		// 		tmp = get_new_from_failure_and(tmp);
		// 	}
		// 	else if (tmp->token.id == OR_IF && job_ret == 0)
		// 		tmp = new_success_or_if(tmp);
		// 	else
		// 	{
		// 		tmp = tmp->right;
		// 		DEBUG("job_ret = %d || TMP ELSE  == %s\n", job_ret, tmp->token.str);
		// 	}
		// 	if (tmp)
		// 		DEBUG("Call split_cmd_jobs %s\n", tmp->token.str);
		// 	split_cmd_jobs(tmp, j->foreground);
//		}
	}
}

void	put_process_in_foreground(t_process *p, int cont)
{
	t_job	*newjob;

	tcsetpgrp(g_shell_terminal, p->pid);
	DEBUG("put foreground \n");
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
