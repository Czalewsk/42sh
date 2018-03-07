/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_process_display.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 09:43:08 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/07 18:36:41 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void    process_display_long(t_process *process)
{
    (void)process;
    //p->pid state: num_signal_2_char'taaaaaaaaaaaaaaaaab'
}

void    process_display_short(t_process *p, char * cmd)
{
    if (p->completed)
    {
        if (WIFSIGNALED(p->status))
            ft_printf("%s", strsignal(WTERMSIG(p->status)));
        else if (p->status == 0)
            ft_printf("Done");
        else
            ft_printf("exit: %d", WEXITSTATUS(p->status));
    }
    else if (p->stopped)
        ft_printf("Stopped");
    else
        ft_printf("Running");
    ft_printf("     %s\n", cmd);
}