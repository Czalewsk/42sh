/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maastie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 21:03:58 by maastie           #+#    #+#             */
/*   Updated: 2018/03/19 11:59:12 by czalewsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sh.h"

int			read_hr(char *hr, char *ref)
{
	if (ft_strlen(hr) - 1 == 0)
		return (-1);
	else if (ft_memcmp(hr, ref, ft_strlen(hr) - 1) != 0)
		return (-1);
	return (0);
}

t_tree		*here_doc(t_process *p, t_tree *c)
{
	int		*fd;

	fd = g_here_list->content;
	close(fd[1]);
	p->stdin = fd[0];
	c = c->right->right;
	while (c && c->token.id == DLESS)
		c = c->right->right;
	ft_lst_remove_index(&g_here_list, 0, NULL);
	return (c);
}

t_tree		*add_new_fd(t_tree *new)
{
	int		fd[2];
	char	*hr;
	int		ret_p;

	if (!g_here_list)
		g_here_list = NULL;
	if (pipe(fd) == -1)
		return ((void *)1);
	hr = NULL;
	while ((ret_p = prompt_add("> ", &hr, 1)) == -2)
	{
		if (ret_p == -1 || read_hr(hr, new->token.str) == 0)
			break ;
		ft_putstr_fd(hr, fd[1]);
		ft_strdel(&hr);
	}
	ft_strdel(&hr);
	if (ret_p == -3)
		return ((void *)1);
	ft_lst_pushend(&g_here_list, ft_lstnew(&fd, sizeof(int *)));
	return (new);
}

t_tree		*add_current_fd(t_tree *new)
{
	char	*hr;
	int		*fd;
	int		ret_p;
	t_list	*tmp;

	tmp = g_here_list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	fd = tmp->content;
	while ((ret_p = prompt_add("> ", &hr, 1)) == -2)
	{
		if (ret_p == -1 || read_hr(hr, new->token.str) == 0)
			break ;
		ft_putstr_fd(hr, fd[1]);
		ft_strdel(&hr);
	}
	ft_strdel(&hr);
	if (ret_p == -3)
		return ((void *)1);
	return (new);
}

t_tree		*here(t_tree *current, t_tree *new)
{
	t_tree	*tmp;

	tmp = current;
	while (tmp)
	{
		tmp = tmp->previous;
		if (tmp && (tmp->token.id == PIPE
			|| tmp->token.id == AND_IF
			|| tmp->token.id == OR_IF))
		{
			break ;
		}
		if (tmp && tmp->token.id == DLESS)
			return (add_current_fd(new));
	}
	return (add_new_fd(new));
}
