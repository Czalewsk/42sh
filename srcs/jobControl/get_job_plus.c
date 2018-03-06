/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_job_plus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:52:42 by scorbion          #+#    #+#             */
/*   Updated: 2018/02/17 18:02:24 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/job_control.h"

t_job   *get_job_plus()
{
    if (job_order != NULL)
        return ((t_job*)(job_order->content));
    return (NULL);
}