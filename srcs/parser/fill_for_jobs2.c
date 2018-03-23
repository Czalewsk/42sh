/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_for_jobs2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 16:01:03 by maastie           #+#    #+#             */
/*   Updated: 2018/03/20 16:01:03 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

void			put_job_at_head_in_job_order(t_job *job)
{
	t_list	*new;

	new = ft_lstnew(NULL, 0);
	new->next = g_job_order;
	g_job_order = new;
	new->content = job;
}

void			put_job_at_end_in_first_job(t_job *job)
{
	t_job	*tmp;

	tmp = g_first_job;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = job;
	else
		g_first_job = job;
}

t_tree			*next_on_tree(t_tree *c, int exit_status)
{
	if (!c)
		return (NULL);
	if (c->token.id == AND_IF && exit_status != 0)
		c = get_new_from_failure_and(c);
	else if (c->token.id == OR_IF && exit_status == 0)
		c = new_success_or_if(c);
	else
		c = c->right;
	return (c);
}

t_job			*get_new_job(t_tree *c, int exit_status, int fg)
{
	t_job		*job;

	if ((c = next_on_tree(c, exit_status)) == NULL)
		return (NULL);
	job = create_new_job(c);
	(void)fg;
	return (job);
}

t_job			*need_norme(t_job *j)
{
	t_job	*res;

	res = get_new_job(j->finish_command, j->status_last_process, j->foreground);
	free_job(j);
	return (res);
}
