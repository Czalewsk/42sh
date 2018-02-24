/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:18:10 by scorbion          #+#    #+#             */
/*   Updated: 2018/02/24 09:59:45 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/job_control.h"

int bt_bg(char **arg)
{
    t_job   *tmp;
    int     i;
    int     retour;

    i = 0;
    retour = 0;
    if (*arg == NULL)
    {
        //42sh: bg: current: no such job
        retour = 1;
    }
    while (arg[i])
    {
        tmp = get_job(arg);
        if (tmp == NULL)
        {
            //42sh: bg: arg: no such job
            retour = 1;
        }
        continue_job(tmp, 0);
        i++;
    }
    return (retour);
}