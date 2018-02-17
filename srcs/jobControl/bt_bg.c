/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:18:10 by scorbion          #+#    #+#             */
/*   Updated: 2018/02/17 17:58:52 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/job_control.h"

int bt_bg(char *arg)
{
    t_job   *tmp;
    
    tmp = get_job(arg);
    if (tmp == NULL)
    {
        if (arg == NULL)
            //42sh: bg: current: no such job
        else
            //42sh: bg: arg: no such job
        return (1);
    }
    continue_job(tmp, 0);
    return (0);
}