/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_job_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 17:49:55 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/03 15:45:51 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_job   *get_job_id(int id)
{
    t_job   *tmp;

    if (first_job == NULL)
        return (NULL);
    tmp = first_job;
    while (tmp != NULL)
    {
        if (tmp->num == id)
            return (tmp);
        tmp = tmp->next;
    }
    return (NULL);
}