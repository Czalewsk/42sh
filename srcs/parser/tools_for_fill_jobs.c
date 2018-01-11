/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_fill_jobs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:07:30 by maastie           #+#    #+#             */
/*   Updated: 2018/01/11 16:07:31 by maastie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

t_tree	*set_end(t_tree *clist, t_job *job)
{
	if (clist->token.id == AND)
		job->notified = 1;
	else if (clist->token.id == OR_IF)
	{
		ft_printf("\nWhere i put this stephane ?\n-->>||<--\n");
	}
	else if (clist->token.id == AND_IF)
	{
		ft_printf("\nWhere i put this stephane ?\n-->>&&<--\n");
	}
	return (clist->right);
}


