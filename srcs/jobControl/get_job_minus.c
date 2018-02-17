/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_job_minus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 17:33:49 by scorbion          #+#    #+#             */
/*   Updated: 2018/02/17 18:02:21 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/job_control.h"

t_job   *get_job_minus()
{
    if (job_order == NULL && job_order->next != NULL)
        return ((t_job*)(tmp->next->content));
    return (NULL);
}