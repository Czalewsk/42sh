/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_job.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:20:16 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/03 18:53:37 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_job   *get_job_id(int id)
{
    t_list      *tmp;
    t_job       *j;

    if (job_order == NULL || job_order->content == NULL)
        return (NULL);
    tmp = job_order;
    while (tmp != NULL)
    {
        j = (t_job*)(tmp->content);
        if (j == NULL)
            continue ;
        if (j->num == id)
            return (j);
        tmp = tmp->next;
    }
    return (NULL);
}

t_job   *get_job_minus()
{
    if (job_order == NULL && job_order->next != NULL)
        return ((t_job*)(job_order->next->content));
    return (NULL);
}

t_job   *get_job_name(char *name)
{
    if (name)
        return (NULL);
    return (NULL);
}

t_job   *get_job_plus()
{
    if (job_order != NULL)
        return ((t_job*)(job_order->content));
    return (NULL);
}

t_job   *get_job(char *arg)
{
    int id;
    
    if (arg == NULL)
        return (get_job_plus());
    if (!ft_strcmp(arg, "%"))
        return (get_job_plus());
    if (!ft_strncmp(arg, "%%", 2))
        return (get_job_plus());
    if (!ft_strncmp(arg, "%+", 2) || !ft_strncmp(arg, "+", 1))
        return (get_job_plus());
    if (!ft_strcmp(arg, "%-") || !ft_strcmp(arg, "-"))
        return (get_job_minus());
    id = ft_atoi(arg);
    if (id != 0)
        return (get_job_id(id));
    return (get_job_name(arg));
}