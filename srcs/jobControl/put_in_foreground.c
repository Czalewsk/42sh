/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_in_foreground.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:28:13 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/18 15:23:14 by scorbion         ###   ########.fr       */
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

t_job	*put_job_in_foreground(t_job *j, int cont)
{
	t_job	*next;
	t_list	*res;
	
	tcsetpgrp(g_shell_terminal, j->pgid);
	if (cont)
	{
		tcsetattr(g_shell_terminal, TCSADRAIN, &j->tmodes);
		if (kill(-j->pgid, SIGCONT) < 0)
			sh_error(1, 0, NULL, 1, "job control: kill SIGCONT");
	}
	print_job(j);
	wait_for_job(j);
	tcsetpgrp(g_shell_terminal, g_shell_pgid);
	tcgetattr(g_shell_terminal, &j->tmodes);
	termcaps_set_tty();

	if (WIFSTOPPED(j->status_last_process))
	{

		display_process_interrupt(j);
		DEBUG("WEXITSTATUS(j->status_last_process) : %d\n", WEXITSTATUS(j->status_last_process))
		next = get_new_job(j->finish_command, WEXITSTATUS(j->status_last_process), j->foreground);
		ft_free_tree(j->finish_command);
		j->finish_command = NULL;
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
		return (next);
	}
	// if (WIFSIGNALED(j->status_last_process))
	// {
	// 	DEBUG("WTERMSIG(j->process->status) %d\n", WTERMSIG(j->process->status))
	// 	if (WTERMSIG(j->status_last_process) == SIGINT)
	// 		write(g_sh.fd_tty, "\n", 1);
	// 	else
	// 		process_display_short(j->process, j->command); //ATTENTION UTILISATION DE FT_PRINTF CAR SAME FONCTION UTILISER PAR JOBS
	// 	ft_free_tree(j->finish_command);
	// 	j->finish_command = NULL;
	// }
	

	// DEBUG("ret job complet : %d\n", job_is_completed(j));
	if (job_is_completed(j))
	{
		res = pop_job_from_job_order(j);
		if (res)
			ft_memdel((void**)&res);
		pop_job_from_first_job(j);
		//next = get_new_job(j->finish_command, WEXITSTATUS(j->status_last_process), j->foreground);
		next = get_new_job(j->finish_command, WIFEXITED(j->status_last_process) ? WEXITSTATUS(j->status_last_process) : 1, j->foreground);
		g_sh.exitstatus = WIFEXITED(j->status_last_process) ? WEXITSTATUS(j->status_last_process) : 1;
		
		// DEBUG("cmd %s, val retour %d\n", j->command, j->process->status);
		// tmp = j->finish_command;

		
		// j->finish_command = NULL;
		// job_ret = j->process->status;
		//get_new_job(tmp2->finish_command, tmp2->status_last_process, tmp2->foreground);

		//ft_free_tree(j->finish_command);
		free_job(j);
		//j->finish_command = NULL;
		
		//del_job(j);
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
		return (next);
	}
	return (NULL);
}
