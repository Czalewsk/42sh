/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_job_plus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:52:42 by scorbion          #+#    #+#             */
/*   Updated: 2018/02/17 16:57:58 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/job_control.h"

t_job   *get_job_plus(char *arg)
{
    if (job_order != NULL)
        return ((t_job*)(job_order->content));
    //erreur : 42sh: fg: arg: no such job
    return (NULL);
}