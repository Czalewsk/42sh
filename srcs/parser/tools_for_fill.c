/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_for_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scorbion <scorbion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:07:30 by maastie           #+#    #+#             */
/*   Updated: 2018/03/06 15:03:10 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

char			*get_command(char *ret, t_tree *chead)
{
	t_tree		*tmp;

	tmp = chead;
	while (tmp->right)
	{
		if (!ret)
			ret = ft_strdup(tmp->token.str);
		else
			ret = ft_strjoin_free(
				ft_strjoin_free(ret, " ", 0), tmp->token.str, 0);
		tmp = tmp->right;
	}
	return (ret);
}

t_tree			*get_new_from_failure_and(t_tree *c)
{
	t_tree		*tmp;

	tmp = c;
	while (tmp)
	{
		if (tmp->token.id == OR_IF)
			return (tmp->right);
		tmp = tmp->right;
	}
	return (tmp);
}

t_tree			*new_success_or_if(t_tree *c)
{
	int			*fd;
	int			a;

	a = 0;
	while (c)
	{
		if (c->token.id == DLESS && a == 0)
		{
			a = 1;
			fd = here_list->content;
			close(fd[0]);
			close(fd[1]);
			ft_lst_remove_index(&here_list, 0, NULL);
		}
		if (c->token.id == AND_IF)
			return (c);
		if (c->token.id == PIPE)
			a = 0;
		c = c->right;
	}
	return (c);
}

void			init_current_process(void)
{
	current_process->next = (t_process *)ft_memalloc(sizeof(t_process));
	current_process = current_process->next;
	current_process->stdout = 1;
	current_process->stderr = 2;
}
