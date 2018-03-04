/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 17:31:13 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/04 10:47:13 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int jobs_display(t_job *j, int long_flag)
{
    ft_printf("[%d]", j->num);
    if (job_order)
    {
        if ((t_job*)(job_order->content) == j)
            ft_printf("+");
        else if (job_order->next && (t_job*)(job_order->next->content) == j)
            ft_printf("-");
        else
            ft_printf(" ");
    }
    ft_printf("  ");
    if (long_flag)
        process_display_long(j->process);
    else
        process_display_short(j->process, j->command);
    return (0);
}

int jobs_display_only_id(t_job *j)
{
    ft_printf("%d\n", j->process->pid);
    return (0);
}