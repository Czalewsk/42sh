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

t_tree	*pipe_process(t_run *run, t_tree *clist)
{
	run->job->first_process->next = init_process(run->job->first_process->next);
	run->job->first_process = run->job->first_process->next;
	return (clist->right);
}

t_tree	*set_end(t_run *run, t_tree *clist)
{
	if (clist->token.id == AND)
	{
		run->num = 1;
		run->job->andor = 0;
	}
	else if (clist->token.id == OR_IF)
	{
		run->job->next = (t_job *)ft_memalloc(sizeof(t_job));
		run->job->andor = 1;
		run->job = run->job->next;
		run->job->first_process = (t_process *)ft_memalloc(sizeof(t_process));

	}
	else if (clist->token.id == AND_IF)
	{
		run->job->next = (t_job *)ft_memalloc(sizeof(t_job));
		run->job->andor = 2;
		run->job = run->job->next;
		run->job->first_process = (t_process *)ft_memalloc(sizeof(t_process));
	}
	else if (clist->token.id == SEMI)
	{
		run->job->andor = 0;
		run->num = 0;
	}
	return (clist->right);
}

char	*get_command(char *ret, t_tree *chead)
{
	t_tree	*tmp;

	tmp = chead;
	while (tmp)
	{
		ret = ft_strjoin_free(ft_strjoin_free(ret, tmp->token.str, 0), " ", 0);
		tmp = tmp->right;
	}
	return (ret);
}