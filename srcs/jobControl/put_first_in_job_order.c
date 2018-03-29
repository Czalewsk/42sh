/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_first_in_job_order.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 10:19:13 by scorbion          #+#    #+#             */
/*   Updated: 2018/03/29 02:18:59 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void	put_last_in_job_order(t_job *j)
{
	t_list	*tmp;

	tmp = pop_job_from_job_order(j);
	if (tmp == NULL)
		return ;
	tmp->next = NULL;
	ft_lst_pushend(&g_job_order, tmp);
}

void	put_first_in_job_order(t_job *j)
{
	t_list	*tmp;

	tmp = pop_job_from_job_order(j);
	if (tmp == NULL)
		return ;
	tmp->next = g_job_order;
	g_job_order = tmp;
}

int		add_after_stopped(t_list *l1, t_list *l2)
{
	(void)l2;
	return (WIFSTOPPED(((t_job*)l1->content)->status_last_process));
}
