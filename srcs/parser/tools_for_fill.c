/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:07:30 by maastie           #+#    #+#             */
/*   Updated: 2018/03/14 19:54:45 by scorbion         ###   ########.fr       */
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

t_tree			*get_new_from_failure_and(t_tree *tmp)
{
	int			a;
	int			*fd;

	a = 0;
	if (tmp)
		DEBUG("*get_new_from_failure_and == %s\n", tmp->token.str);
	while (tmp)
	{
		if (tmp->token.id == DLESS && a == 0)
		{
			a = 1;
			fd = g_here_list->content;
			close(fd[0]);
			close(fd[1]);
			ft_lst_remove_index(&g_here_list, 0, NULL);
		}
		if (tmp->token.id == OR_IF)
			return (tmp->right);
		if (tmp->token.id == PIPE || tmp->token.id == AND_IF)
			a = 0;
		tmp = tmp->right;
	}
	if (tmp)
		DEBUG("*get_new_from_failure_and == %s\n", tmp->token.str);
	return (tmp);
}

t_tree			*new_success_or_if(t_tree *c)
{
	int			*fd;
	int			a;

	a = 0;
	DEBUG("*new_success_or_if token == %s\n", c->token.str);
	while (c)
	{
		if (c->token.id == DLESS && a == 0)
		{
			a = 1;
			fd = g_here_list->content;
			close(fd[0]);
			close(fd[1]);
			ft_lst_remove_index(&g_here_list, 0, NULL);
		}
		if (c->token.id == AND_IF)
			return (c->right);
		if (c->token.id == PIPE || c->token.id == OR_IF)
			a = 0;
		c = c->right;
	}
	if (c)
		DEBUG("*new_success_or_if token == %s\n", c->token.str);
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
