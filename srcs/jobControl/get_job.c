/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_job.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 16:20:16 by scorbion          #+#    #+#             */
/*   Updated: 2018/02/17 16:57:24 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/job_control.h"

t_job   *get_job(char *arg)
{
    int id;
    
    if (arg == NULL)
        return (get_job_plus(arg));
    if (!ft_strcmp(arg, "%"))
        return (get_job_plus(arg));
    if (!ft_strncmp(arg, "%%", 2))
        return (get_job_plus(arg));
    if (!ft_strncmp(arg, "%+", 2) || !ft_strncmp(arg, "+", 1))
        return (get_job_plus(arg));
    if (!ft_strcmp(arg, "%-") || !ft_strcmp(arg, "-"))
        return (get_job_minus(arg));
    id = ft_atoi(arg);
    if (id != 0)
        return (get_job_id(arg, id));
    return (get_job_name(arg));
}