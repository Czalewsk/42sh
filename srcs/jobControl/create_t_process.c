/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_t_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 11:41:30 by scorbion          #+#    #+#             */
/*   Updated: 2018/01/18 11:46:54 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int create_t_process(t_process **ptr)
{
    *ptr = (t_process*)memalloc(sizeof(t_process));
    if (*ptr != NULL)
        return (0);
    perror("fail memalloc create_t_process");
    return (1);
}