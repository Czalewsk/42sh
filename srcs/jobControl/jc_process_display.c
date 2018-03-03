/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_process_display.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 09:43:08 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/03 12:47:38 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/job_control.h"

void    process_display_long(t_process *process)
{
    (void*)process;
    //p->pid state: num_signal_2_char'taaaaaaaaaaaaaaaaab'
}

void    process_display_short(t_process *process, char * cmd)
{
    if (p->completed)
    {
        if (WIFSIGNALED(p->status))
            ft_printf("%s: %d", strsignal(WTERMSIG(p->status)), WTERMSIG(p->status));
        else if (status == 0)
            ft_printf("Done");
        else
            ft_printf("exit: %d", WEXITSTATUS(status));
    }
    else if (p->stopped)
        ft_printf("Stopped");
    else
        ft_printf("Running");
    ft_printf("     %s\n", cmd);
}