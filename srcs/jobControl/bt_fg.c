/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_fg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:08:50 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/03 15:43:53 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int bt_fg(char **arg)
{
    t_job   *tmp;

    tmp = get_job(*arg);
    if (tmp == NULL)
    {
        if (arg == NULL)
            sh_error(0, 0, NULL, 1, "fg: current: no such job");
        else
            sh_error(0, 0, NULL, 3, "fg: ", *arg, ": no such job");
        return (1);
    }
    continue_job(tmp, 1);
    return (0);
}