/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_first_in_job_order.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 10:19:13 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/11 11:17:43 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	put_first_in_job_order(t_job *j)
{
	t_list	*tmp;

	tmp = pop_job_from_job_order(j);
	if (tmp == NULL)
		return ;
	tmp->next = g_job_order;
	g_job_order = tmp;
}
