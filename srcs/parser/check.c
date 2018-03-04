/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:55:12 by maastie           #+#    #+#             */
/*   Updated: 2018/02/24 20:55:13 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_tree		*get_the_rest(t_tree *c)
{
	t_tree	*new;
	t_tree	*sn;
	t_tree	*tmp;

	tmp = c;
	while (tmp)
	{
		if (!new)
		{
			new = (t_tree *)ft_memalloc(sizeof(t_tree));
			new->token.str = ft_strdup(tmp->token.str);
			new->token.id = tmp->token.id;
			sn = new;
		}
		else
		{
			new = new->right;
			new = (t_tree *)ft_memalloc(sizeof(t_tree));
			new->token.str = ft_strdup(tmp->token.str);
			new->token.id = tmp->token.id;
		}
		tmp = tmp->right;
	}
	return (sn);
}

t_tree		*get_new_process_from_valid_or_if(t_tree *c)
{
	while (c)
	{
		c = c->right;
		if (c && c->token.id == AND_IF)
			return (c->right);
	}
	return (c);
}

t_tree		*get_new_process_from_pipe(t_tree *c)
{
	while (c)
	{
		c = c->right;
		if (c && c->token.id == AND_IF)
		{
			if (g_sh.exitstatus == -1)
				return (NULL);
			return (c->right);
		}
		else if (c && c->token.id == OR_IF)
		{
			if (g_sh.exitstatus == 0)
				return (c = get_new_process_from_valid_or_if(c));
			return (c->right);
		}
	}
	return (c);
}

t_tree		*check_or_if(t_tree *tmp, t_tree *stop, t_job *job)
{
	if (job)
	{
		job->foni = 1;
		if (job->finish_oni)
			ft_free_tree(job->finish_oni);
		job->finish_oni = get_the_rest(stop->right);
	}
	if ((g_sh.exitstatus = execute_run(tmp, stop, job)) == 0)
		return (tmp = get_new_process_from_valid_or_if(stop->right));
	return (stop->right);
}

t_tree		*check_and_if(t_tree *tmp, t_tree *stop, t_job *job)
{
	if (job)
	{
		job->foni = 2;
		if (job->finish_oni)
			ft_free_tree(job->finish_oni);
		job->finish_oni = get_the_rest(stop->right);
	}
	if ((g_sh.exitstatus = execute_run(tmp, stop, job)) != 0)
		return ((void *)1);
	return (stop->right);
}

t_tree		*check_pipe(t_tree *tmp, t_tree *stop, t_job *job)
{
	if (job)
	{
		job->foni = 0;
		if (job->finish_oni)
			ft_free_tree(job->finish_oni);
		job->finish_oni = get_the_rest(stop->right);
	}
	if ((g_sh.exitstatus = set_for_pipe(tmp, job)) == 0)
		return (tmp = get_new_process_from_pipe(stop));
	return ((void *)1);
}
