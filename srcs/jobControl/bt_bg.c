/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_bg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:18:10 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/03 15:45:18 by scorbion         ###   ########.fr       */
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
        //42sh: bg: current: no such job
        retour = 1;
    }
    while (arg[i])
    {
        tmp = get_job(arg[i]);
        if (tmp == NULL)
        {
            //42sh: bg: arg[i]: no such job
            retour = 1;
        }
        continue_job(tmp, 0);
        i++;
    }
    return (retour);
}