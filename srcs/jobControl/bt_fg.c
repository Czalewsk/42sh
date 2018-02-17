/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:08:50 by scorbion          #+#    #+#             */
/*   Updated: 2018/02/17 16:18:19 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/job_control.h"

int bt_fg(char *arg)
{
    t_job   *tmp;

    tmp = get_job(arg);
    if (tmp == NULL)
        return (1);
    continue_job(tmp, 1);
    return (0);
}