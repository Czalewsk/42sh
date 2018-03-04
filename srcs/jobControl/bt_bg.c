/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:18:10 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/04 09:39:23 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int bt_bg(char **arg)
{
    t_job   *tmp;
    int     i;
    int     retour;

    i = 0;
    retour = 0;
    if (*arg == NULL)
    {
        sh_error(0, 0, NULL, 1, "bg: current: no such job\n");
        retour = 1;
    }
    while (arg[i])
    {
        tmp = get_job(arg[i]);
        if (tmp == NULL)
        {
            sh_error(0, 0, NULL, 3, "fg: ", *arg, ": no such job\n");
            retour = 1;
        }
        else
            continue_job(tmp, 0);
        i++;
    }
    return (retour);
}