/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_current_job.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 10:19:13 by scorbion          #+#    #+#             */
/*   Updated: 2018/02/24 11:10:17 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/job_control.h"

static t_list  *pop_job_order_by_job(t_job *j)
{
    t_list  *tmp;
    t_list  *target;

    tmp = job_order;
    if ((t_job*)tmp->content == j)
        return (NULL);
    while (tmp->next && (t_job*)tmp->next->content != j)
        tp = tmp->next;
    if (tmp->next == NULL)
    {
        //42sh: job_control: erreur impossible de trouver le job dans la liste job_order
        return (NULL);
    }
    target = tmp->next;
    tmp->next = tmp->next->next;
    return (target);
}


void            put_first_in_job_order(t_job *j)
{
    t_list  *tmp;

    tmp = pop_list_by_job(j);
    if (tmp == NULL)
        return ;
    tmp->next = job_order;
    job_order = tmp;
}