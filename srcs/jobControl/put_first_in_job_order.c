/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_first_in_job_order.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 10:19:13 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/09 17:34:20 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

// static t_list  *pop_listjob_from_job_order(t_job *j)
// {
//     t_list  *tmp;
//     t_list  *target;

//     tmp = job_order;
//     if ((t_job*)tmp->content == j)
//         return (NULL);
//     while (tmp->next && (t_job*)tmp->next->content != j)
//         tmp = tmp->next;
//     if (tmp->next == NULL)
//     {
//         sh_error(1, 0, NULL, 1, "job not found in job order");
//         return (NULL);
//     }
//     target = tmp->next;
//     tmp->next = tmp->next->next;
//     return (target);
// }


void            put_first_in_job_order(t_job *j)
{
    t_list  *tmp;

    tmp = pop_job_from_job_order(j);
    if (tmp == NULL)
        return ;
    tmp->next = job_order;
    job_order = tmp;
}