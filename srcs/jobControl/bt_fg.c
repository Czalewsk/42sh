/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:08:50 by scorbion          #+#    #+#             */
/*   Updated: 2018/02/24 11:12:15 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/job_control.h"

int bt_fg(char **arg)
{
    t_job   *tmp;

    tmp = get_job(*arg);
    if (tmp == NULL)
    {
        if (arg == NULL)
            //42sh: fg: current: no such job
        else
            //42sh: fg: *arg: no such job
        return (1);
    }
    continue_job(tmp, 1);
    return (0);
}