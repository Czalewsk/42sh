/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:18:10 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/09 19:45:31 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

static void    bg_launch(t_job *j)
{
    char    *num;

    num = ft_itoa(j->num);
    if (job_is_stopped(j) != 0 && job_is_completed(j) != 0)
        sh_error(0, 0, NULL, 3, "bg: job ", num, " already in background\n");
    else
    {
        ft_printf("[%s]", num);
        if (job_order)
        {
            if ((t_job*)(job_order->content) == j)
                ft_printf("+");
            else if (job_order->next && (t_job*)(job_order->next->content) == j)
                ft_printf("-");
            else
                ft_printf(" ");
        }
        ft_printf(" %s &\n", j->command);
        put_first_in_job_order(j);
        continue_job(j, 0);
    }
    free(num);
}

int             bt_bg(char **arg)
{
    t_job   *tmp;
    int     i;
    int     retour;

    i = 0;
    retour = 0;
    if (*arg == NULL)
    {
        tmp = get_job(NULL);
        if (tmp == NULL)
            retour = sh_error(1, 0, NULL, 1, "bg: current: no such job\n");
        else
            bg_launch(tmp);
    }
    while (arg[i])
    {
        tmp = get_job(arg[i]);
        if (tmp == NULL)
            retour = sh_error(1, 0, NULL, 3, "bg: ", *arg, ": no such job\n");
        else
            bg_launch(tmp);
        i++;
    }
    return (retour);
}