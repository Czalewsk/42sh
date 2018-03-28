/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:07:30 by maastie           #+#    #+#             */
/*   Updated: 2018/03/27 15:09:16 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char			*get_command(char *ret, t_tree *chead)
{
	t_tree		*tmp;

	tmp = chead;
	while (tmp)
	{
		if (tmp->token.id == AND_IF || tmp->token.id == OR_IF)
			break ;
		if (!ret)
			ret = ft_strdup(tmp->token.str);
		else
			ret = ft_strjoin_free(
				ft_strjoin_free(ret, " ", 0), tmp->token.str, 0);
		tmp = tmp->right;
	}
	return (ret);
}

void			close_skiped_here(void)
{
	t_list		*tmp;
	t_here		*tmpp;
	int			ref_here;

	tmp = g_here_list;
	tmpp = tmp->content;
	ref_here = tmpp->num;
	while (tmp)
	{
		tmpp = tmp->content;
		tmp = tmp->next;
		if (tmpp->num != ref_here)
			break ;
		close(tmpp->fd[0]);
		close(tmpp->fd[1]);
		ft_lst_remove_index(&g_here_list, 0, NULL);
	}
}

t_tree			*get_new_from_failure_and(t_tree *tmp)
{
	while (tmp)
	{
		if (tmp->token.id == DLESS)
		{
			close_skiped_here();
			while (tmp && (tmp->token.id != OR_IF
				&& tmp->token.id != AND_IF && tmp->token.id != PIPE))
				tmp = tmp->right;
			if (!tmp)
				return (tmp);
		}
		if (tmp->token.id == OR_IF)
			return (tmp->right);
		tmp = tmp->right;
	}
	return (tmp);
}

t_tree			*new_success_or_if(t_tree *c)
{
	while (c)
	{
		if (c->token.id == DLESS)
		{
			close_skiped_here();
			while (c && (c->token.id != OR_IF
				&& c->token.id != AND_IF && c->token.id != PIPE))
				c = c->right;
			if (!c)
				return (c);
		}
		if (c->token.id == AND_IF)
			return (c->right);
		c = c->right;
	}
	return (c);
}

void			init_current_process(t_tree *c, t_job *job)
{
	job->process->next = (t_process *)ft_memalloc(sizeof(t_process));
	if (job->command)
		ft_strdel(&job->command);
	job->command = get_command(job->command, c);
	job->process = job->process->next;
	job->process->stdout = 1;
	job->process->stderr = 2;
}
