/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 20:55:12 by maastie           #+#    #+#             */
/*   Updated: 2018/03/03 20:21:54 by scorbion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

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
	if ((g_sh.exitstatus = execute_run(tmp, stop, job)) == 0)
		return (tmp = get_new_process_from_valid_or_if(stop->right));
	return (stop->right);
}

t_tree		*check_and_if(t_tree *tmp, t_tree *stop, t_job *job)
{	
	if ((g_sh.exitstatus = execute_run(tmp, stop, job)) != 0)
		return ((void *)1);
	return (stop->right);
}

t_tree		*check_pipe(t_tree *tmp, t_tree *stop, t_job *job)
{
	if ((g_sh.exitstatus = set_for_pipe(tmp, job)) == 0)
		return (tmp = get_new_process_from_pipe(stop));
	return ((void *)1);
}
