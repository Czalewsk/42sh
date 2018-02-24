/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 17:31:13 by scorbion          #+#    #+#             */
/*   Updated: 2018/02/24 18:31:13 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/job_control.h"

int jobs_display(t_job *j)
{
    int     is_current;
    int     is_old_current;
    char    *status;

    ft_printf("[%d]", j->num);
    if (job_order)
    {
        if ((t_job*)(job_order->content) == j)
            ft_printf("+")
        else if (job_order->next && (t_job*)(job_order->next->content) == j)
            ft_printf("-")
        else
            ft_printf(" ");
    }
    ft_printf("  ");
    process_display(j->process);
    return (0);
}

int jobs_display_only_id(t_job *j)
{
    ft_printf("%d", j->process->pid);
}