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

t_tree		*check_or_if(t_tree *tmp, t_tree *stop)
{
	if ((g_sh.exitstatus = execute_run(tmp, stop, NULL)) == 0)
		return (tmp = get_new_process_from_valid_or_if(stop->right));
	return (stop->right);
}

t_tree		*check_and_if(t_tree *tmp, t_tree *stop)
{
	if ((g_sh.exitstatus = execute_run(tmp, stop, NULL)) != 0)
		return ((void *)1);
	return (stop->right);
}

t_tree		*check_pipe(t_tree *tmp, t_tree *stop)
{
	if ((g_sh.exitstatus = set_for_pipe(tmp)) == 0)
		return (tmp = get_new_process_from_pipe(stop));
	return ((void *)1);
}
